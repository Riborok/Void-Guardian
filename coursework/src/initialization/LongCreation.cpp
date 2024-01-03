#include "../../include/initialization/LongCreation.hpp"
#include <thread>

Launcher* LongCreation::createLauncher(GameSetup& game_setup) {
    Launcher* result = nullptr;
    std::thread data_init_thread([&result, &game_setup] {
        result = new Launcher(game_setup);
        game_setup.loading_screen.end();
    });

    game_setup.loading_screen.start();
    data_init_thread.join();
    
    return result;
}

GameMaster* LongCreation::createGameMaster(GameSetup& game_setup, const GameData& game_data) {
    GameMaster* result = nullptr;
    std::thread data_init_thread([&result, &game_setup, &game_data] {
        result = new GameMaster(game_setup.game_context, game_data);
        game_setup.loading_screen.end();
    });

    game_setup.loading_screen.start();
    data_init_thread.join();
    
    return result;
}

void LongCreation::freeGameMaster(GameSetup& game_setup, GameMaster* game_master) {
    std::thread data_init_thread([&game_setup, &game_master] {
        delete game_master;
        game_setup.loading_screen.end();
    });

    game_setup.loading_screen.start();
    data_init_thread.join();
}