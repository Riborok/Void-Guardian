#pragma once
#include <SFML/Window/Keyboard.hpp>

#include "FullscreenToggler.h"

class HotkeyManager final {
    FullscreenToggler _fullscreen_toggler;
public:
    explicit HotkeyManager(FullscreenToggler &&fullscreen_toggler) : _fullscreen_toggler(std::move(fullscreen_toggler)) { }
    
    void handleHotkeys(const sf::Keyboard::Key key_code) {
        // ReSharper disable once CppDefaultCaseNotHandledInSwitchStatement CppIncompleteSwitchStatement
        switch (key_code) {  // NOLINT(hicpp-multiway-paths-covered, clang-diagnostic-switch)
            case sf::Keyboard::F11:
                _fullscreen_toggler.toggleFullscreen();
                break;
        }
    }
    ~HotkeyManager() noexcept = default;
    
    HotkeyManager(const HotkeyManager&) noexcept = delete;
    HotkeyManager& operator=(const HotkeyManager&) noexcept = delete;
    HotkeyManager(HotkeyManager&&) noexcept = delete;
    HotkeyManager& operator=(HotkeyManager&&) noexcept = delete;
};
