#pragma once
#include <SFML/Window/Keyboard.hpp>

#include "FullscreenToggler.hpp"

enum class HotkeyManagerResult {
    NONE,
    TOGGLE_FULLSCREEN,
};

class HotkeyManager final {
    FullscreenToggler _fullscreen_toggler;
public:
    explicit HotkeyManager(FullscreenToggler &&fullscreen_toggler);

    HotkeyManagerResult handleHotkeys(const sf::Keyboard::Key key_code);
    
    ~HotkeyManager() noexcept = default;
    
    HotkeyManager(const HotkeyManager&) noexcept = delete;
    HotkeyManager& operator=(const HotkeyManager&) noexcept = delete;
    HotkeyManager(HotkeyManager&&) noexcept = delete;
    HotkeyManager& operator=(HotkeyManager&&) noexcept = delete;
};
