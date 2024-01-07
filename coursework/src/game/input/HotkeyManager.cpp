// ReSharper disable CppDefaultCaseNotHandledInSwitchStatement CppIncompleteSwitchStatement CppClangTidyClangDiagnosticSwitch
#include "../../../include/game/input/HotkeyManager.hpp"

HotkeyManager::HotkeyManager(FullscreenToggler &fullscreen_toggler, GameState &game_state):
    _fullscreen_toggler(&fullscreen_toggler), _game_state(&game_state) {}

HotkeyManagerResult HotkeyManager::handleHotkeys(const sf::Keyboard::Key key_code) const {
    switch (key_code) {
    case FullscreenToggler::DEFAULT_KEYBOARD_SWITCH:
        _fullscreen_toggler->toggleFullscreen();
        return HotkeyManagerResult::TOGGLE_FULLSCREEN;
    case sf::Keyboard::Escape:
        *_game_state = GameState::RETURN_TO_MENU;
        return HotkeyManagerResult::RETURN_TO_MENU;
    }

    return HotkeyManagerResult::NONE;
}
