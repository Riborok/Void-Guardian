// ReSharper disable CppDefaultCaseNotHandledInSwitchStatement CppIncompleteSwitchStatement CppClangTidyClangDiagnosticSwitch
#include "../../../include/game/input/HotkeyManager.hpp"

HotkeyManager::HotkeyManager(ToggleFullscreen &&toggle_fullscreen, SetPause &&set_pause):
    _toggle_fullscreen(std::move(toggle_fullscreen)), _set_pause(std::move(set_pause)){}

void HotkeyManager::handleHotkeys(const sf::Keyboard::Key key_code) const {
    switch (key_code) {
    case FullscreenToggler::DEFAULT_KEYBOARD_SWITCH:
        _toggle_fullscreen();
        break;
    case sf::Keyboard::Escape:
        _set_pause();
        break;
    }
}
