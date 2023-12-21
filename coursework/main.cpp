#include "include/files/FileManager.hpp"
#include "include/game/GameData.hpp"
#include "include/game/GameMaster.hpp"
#include "include/initialization/GameDataInitialization.hpp"

void startGame(sf::RenderWindow &window, PlayerProgress player_progress, const Control &control) {
    const auto* game_data = new GameData(GameDataInitialization::initializeGameData());
    FullscreenToggler fullscreen_toggler(window, GameDataInitialization::initializeWindowInfo(), false);

    GameState game_state;
    do {
        auto *game_master = new GameMaster(window, fullscreen_toggler, player_progress, control, *game_data);
        game_master->start();
        
        if (game_state = game_master->getGameState(); game_state == GameState::NEXT_LEVEL) {
            ++player_progress.lvl;
            player_progress.player_inventory = game_master->getPlayerInventory();
        }
        
        delete game_master;
    } while (game_state == GameState::NEXT_LEVEL);
    
    delete game_data;
    
    /*if (game_state == GameState::LOSE)  { FileManager::deleteProgressFile(); }
    else                                { FileManager::savePlayerProgress(player_progress); }*/
}

void main() {
    auto *window = new sf::RenderWindow();
    
    /*FileManager::checkDataFiles();
    const PlayerProgress player_progress = FileManager::hasProgress()
        ? FileManager::loadPlayerProgress()
        : PlayerProgress{{0, 0}, 0};*/
    FileManager file_manager;
    PlayerProgress player_progress; file_manager.loadOrGetDefault(player_progress);
    player_progress.player_inventory.character_num = 3;
    Control control;                file_manager.loadOrGetDefault(control);
    
    startGame(*window, player_progress, control);
    
    delete window;
}