#include "../include/Launcher.hpp"
#include "../include/game/GameState.hpp"
#include "..\include\initialization\InfoInitialization.hpp"

Launcher::Launcher(GameSetup &game_setup):
        _game_setup(&game_setup),
        _menu_controller(*_game_setup,
            *_game_setup->ui_controller.font, _game_setup->game_context.fullscreen_toggler.getTitle(),
            InfoInitialization::initializeAboutUrl(),
            *_game_setup->ui_controller.cursors, InfoInitialization::initializeColors()),
        _game_starter(*_game_setup, _game_setup->ui_controller.pause_controller,
            InfoInitialization::initializeGameInfo(), InfoInitialization::initializeAimCursorSrc(),
            InfoInitialization::initializeColors(), InfoInitialization::initializeCharacterLimits()) {
    _file_operator.loadOrGetDefault(_game_setup->game_context.player_progress);
    _file_operator.loadOrGetDefault(_game_setup->game_context.control);
}

void Launcher::start() {
    GameState game_state;
    do {
        _menu_controller.startMenu();
        if (_game_setup->game_context.window.isOpen()) {
            game_state = _game_starter.startGame();
            if (game_state == GameState::LOSE)  { _game_setup->game_context.player_progress = {}; }
        }
        else
            break;
    } while(game_state == GameState::RETURN_TO_MENU || game_state == GameState::LOSE);
    _file_operator.save(_game_setup->game_context.player_progress);
    _file_operator.save(_game_setup->game_context.control);
}