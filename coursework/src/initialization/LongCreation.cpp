#include "../../include/initialization/LongCreation.hpp"
#include <thread>

Launcher* LongCreation::createLauncher(GameSetup& game_setup) {
    Launcher* result = nullptr;
    std::thread thread([&result, &game_setup] {
        result = new Launcher(game_setup);
        game_setup.ui_controller.loading_screen.end();
    });

    game_setup.ui_controller.loading_screen.start();
    thread.join();
    
    return result;
}

GameMaster* LongCreation::createGameMaster(GameSetup& game_setup, PauseSubset &pause_subset, const GameInfo& game_info) {
    GameMaster* result = nullptr;
    std::thread thread([&result, &game_setup, &pause_subset, &game_info] {
        result = new GameMaster(game_setup.game_context, pause_subset, game_info);
        game_setup.ui_controller.loading_screen.end();
    });

    game_setup.ui_controller.loading_screen.start();
    thread.join();
    
    return result;
}

void LongCreation::freeGameMaster(GameSetup& game_setup, GameMaster* game_master) {
    std::thread thread([&game_setup, &game_master] {
        delete game_master;
        game_setup.ui_controller.loading_screen.end();
    });

    game_setup.ui_controller.loading_screen.start();
    thread.join();
}