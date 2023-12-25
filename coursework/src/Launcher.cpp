#include "../include/Launcher.hpp"
#include "../include/game/GameMaster.hpp"
#include "../include/game/GameState.hpp"
#include "../include/initialization/GameDataInitialization.hpp"

void Launcher::setDefaultTitle() {
    _window.setTitle(_fullscreen_toggler.getTitle());
}

void Launcher::startMenu() {
    setDefaultTitle();
    _menu_manager.startMenu();
}

void Launcher::setLvlTitle() {
    _window.setTitle("Current lvl: " + std::to_string(_player_progress.lvl));
}

GameState Launcher::startGame() {
    const auto* game_data = new GameData(GameDataInitialization::initializeGameData());

    GameState game_state;
    do {
        setLvlTitle();
        auto *game_master = new GameMaster(_window, _fullscreen_toggler, _player_progress, _control, *game_data);
        game_master->start();
        
        if (game_state = game_master->getGameState(); game_state == GameState::NEXT_LEVEL) {
            ++_player_progress.lvl;
            _player_progress.player_inventory = game_master->getPlayerInventory();
        }
        
        delete game_master;
    } while (game_state == GameState::NEXT_LEVEL);
    delete game_data;
    return game_state;
}

Launcher::Launcher(): _window(),
        _fullscreen_toggler(_window, GameDataInitialization::initializeWindowInfo(),
            false),
        _file_manager(),
        _player_progress(), _control(),
        _menu_manager(_window, _fullscreen_toggler, _player_progress, _control){
    _file_manager.loadOrGetDefault(_player_progress);
    _file_manager.loadOrGetDefault(_control);
}

void Launcher::start() {
    GameState game_state;
    do {
        startMenu();
        if (_window.isOpen()) {
            game_state = startGame();
            if (game_state == GameState::LOSE)  { _player_progress = {}; }
        }
        else
            break;
    } while(game_state == GameState::RETURN_TO_MENU || game_state == GameState::LOSE);
    _file_manager.save(_player_progress);
    _file_manager.save(_control);
}