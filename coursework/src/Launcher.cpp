#include "../include/Launcher.hpp"
#include "../include/game/GameMaster.hpp"
#include "../include/game/GameState.hpp"
#include "../include/initialization/DataInitialization.hpp"

Launcher::Launcher(): _game_context(DataInitialization::initializeWindowInfo()),
        _game_manager(_game_context, DataInitialization::initializeGameData(),
            DataInitialization::initializeAimCursorSrc()),
        _menu_manager(_game_context, DataInitialization::initializeMenuManagerInfo(
            _game_context.fullscreen_toggler.getTitle())) {
    _file_manager.loadOrGetDefault(_game_context.player_progress);
    _file_manager.loadOrGetDefault(_game_context.control);
}

void Launcher::start() {
    GameState game_state;
    do {
        _menu_manager.startMenu();
        if (_game_context.window.isOpen()) {
            game_state = _game_manager.startGame();
            if (game_state == GameState::LOSE)  { _game_context.player_progress = {}; }
        }
        else
            break;
    } while(game_state == GameState::RETURN_TO_MENU || game_state == GameState::LOSE);
    _file_manager.save(_game_context.player_progress);
    _file_manager.save(_game_context.control);
}