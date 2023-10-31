#pragma once
#include <SFML/Window/Keyboard.hpp>

#include "FullscreenToggler.h"

class HotkeyManager {
    FullscreenToggler _fullscreen_toggler;
public:
    explicit HotkeyManager(FullscreenToggler &&fullscreen_toggler) : _fullscreen_toggler(std::move(fullscreen_toggler)) { }
    
    void handleHotkeys(const int key_code) {
        // ReSharper disable once CppDefaultCaseNotHandledInSwitchStatement
        switch (key_code) {
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
