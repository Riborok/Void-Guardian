// ReSharper disable CppDefaultCaseNotHandledInSwitchStatement CppIncompleteSwitchStatement CppClangTidyClangDiagnosticSwitch
#include "../../../include/game/input/HotkeyHandler.hpp"

#include "../../../include/gui/ReservedKeys.hpp"

HotkeyHandler::HotkeyHandler(ToggleFullscreen &&toggle_fullscreen, SetPause &&set_pause):
    _toggle_fullscreen(std::move(toggle_fullscreen)), _set_pause(std::move(set_pause)){}

void HotkeyHandler::handleHotkeys(const sf::Keyboard::Key key_code) const {
    switch (key_code) {
    case ReservedKeys::FULL_SCREEN_TOGGLE:
        _toggle_fullscreen();
        break;
    case ReservedKeys::BACK:
        _set_pause();
        break;
    }
}
