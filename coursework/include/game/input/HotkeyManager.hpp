#pragma once
#include <functional>
#include <SFML/Window/Keyboard.hpp>
#include "../../additionally/FunctionCreator.hpp"

class HotkeyManager final {
    ToggleFullscreen _toggle_fullscreen;
    SetPause _set_pause;
public:
    HotkeyManager(ToggleFullscreen &&toggle_fullscreen, SetPause &&set_pause);
    void handleHotkeys(const sf::Keyboard::Key key_code) const;
    
    ~HotkeyManager() noexcept = default;
    
    HotkeyManager(const HotkeyManager&) noexcept = delete;
    HotkeyManager& operator=(const HotkeyManager&) noexcept = delete;
    HotkeyManager(HotkeyManager&&) noexcept = delete;
    HotkeyManager& operator=(HotkeyManager&&) noexcept = delete;
};
