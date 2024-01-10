// ReSharper disable CppDefaultCaseNotHandledInSwitchStatement CppIncompleteSwitchStatement CppClangTidyClangDiagnosticSwitch
#include "../../../include/game/input/HotkeyManager.hpp"

#include "../../../include/gui/ReservedKeys.hpp"

HotkeyManager::HotkeyManager(ToggleFullscreen &&toggle_fullscreen, SetPause &&set_pause):
    _toggle_fullscreen(std::move(toggle_fullscreen)), _set_pause(std::move(set_pause)){}

void HotkeyManager::handleHotkeys(const sf::Keyboard::Key key_code) const {
    switch (key_code) {
    case ReservedKeys::FULL_SCREEN_TOGGLE:
        _toggle_fullscreen();
        break;
    case ReservedKeys::BACK:
        _set_pause();
        break;
    }
}
