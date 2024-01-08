#include "../include/Launcher.hpp"
#include "../include/game/GameState.hpp"
#include "../include/initialization/DataInitialization.hpp"

Launcher::Launcher(GameSetup &game_setup):
        _game_setup(&game_setup),
        _menu_manager(*_game_setup,
            {*_game_setup->gui_manager.font, _game_setup->game_context.fullscreen_toggler.getTitle(), DataInitialization::initializeAboutUrl()},
            *_game_setup->gui_manager.cursors, DataInitialization::initializeColors()),
        _game_manager(*_game_setup, _game_setup->gui_manager.pause_manager,
            DataInitialization::initializeGameData(), DataInitialization::initializeAimCursorSrc(),
            DataInitialization::initializeColors(), DataInitialization::initializeCharacterLimits()) {
    _file_manager.loadOrGetDefault(_game_setup->game_context.player_progress);
    _file_manager.loadOrGetDefault(_game_setup->game_context.control);
}

void Launcher::start() {
    GameState game_state;
    do {
        _menu_manager.startMenu();
        if (_game_setup->game_context.window.isOpen()) {
            game_state = _game_manager.startGame();
            if (game_state == GameState::LOSE)  { _game_setup->game_context.player_progress = {}; }
        }
        else
            break;
    } while(game_state == GameState::RETURN_TO_MENU || game_state == GameState::LOSE);
    _file_manager.save(_game_setup->game_context.player_progress);
    _file_manager.save(_game_setup->game_context.control);
}