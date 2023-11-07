// ReSharper disable CppDefaultCaseNotHandledInSwitchStatement CppIncompleteSwitchStatement CppClangTidyClangDiagnosticSwitch
#include "../../../include/game/input/HotkeyManager.hpp"

HotkeyManager::HotkeyManager(FullscreenToggler &&fullscreen_toggler)
    : _fullscreen_toggler(std::move(fullscreen_toggler)) {}

HotkeyManagerResult HotkeyManager::handleHotkeys(const sf::Keyboard::Key key_code) {
    switch (key_code) {
    case sf::Keyboard::F11:
        _fullscreen_toggler.toggleFullscreen();
        return HotkeyManagerResult::TOGGLE_FULLSCREEN;
    }

    return HotkeyManagerResult::NONE;
}