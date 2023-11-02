#pragma once
#include <SFML/Window/Keyboard.hpp>

#include "FullscreenToggler.h"

enum HotkeyManagerResult {
    NONE,
    TOGGLE_FULLSCREEN,
};

class HotkeyManager final {
    FullscreenToggler _fullscreen_toggler;
public:
    explicit HotkeyManager(FullscreenToggler &&fullscreen_toggler) : _fullscreen_toggler(std::move(fullscreen_toggler)) { }
    
    HotkeyManagerResult handleHotkeys(const sf::Keyboard::Key key_code) {
        // ReSharper disable once CppDefaultCaseNotHandledInSwitchStatement CppIncompleteSwitchStatement
        switch (key_code) {  // NOLINT(hicpp-multiway-paths-covered, clang-diagnostic-switch)
            case sf::Keyboard::F11:
                _fullscreen_toggler.toggleFullscreen();
                return TOGGLE_FULLSCREEN;
        }
        
        return NONE;
    }
    ~HotkeyManager() noexcept = default;
    
    HotkeyManager(const HotkeyManager&) noexcept = delete;
    HotkeyManager& operator=(const HotkeyManager&) noexcept = delete;
    HotkeyManager(HotkeyManager&&) noexcept = delete;
    HotkeyManager& operator=(HotkeyManager&&) noexcept = delete;
};
