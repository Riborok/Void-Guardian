#pragma once
#include <functional>
#include <SFML/Window/Keyboard.hpp>
#include "../../additionally/FunctionCreator.hpp"

class HotkeyHandler final {
    ToggleFullscreen _toggle_fullscreen;
    SetPause _set_pause;
public:
    HotkeyHandler(ToggleFullscreen &&toggle_fullscreen, SetPause &&set_pause);
    void handleHotkeys(const sf::Keyboard::Key key_code) const;
    
    ~HotkeyHandler() noexcept = default;
    
    HotkeyHandler(const HotkeyHandler&) noexcept = delete;
    HotkeyHandler& operator=(const HotkeyHandler&) noexcept = delete;
    HotkeyHandler(HotkeyHandler&&) noexcept = delete;
    HotkeyHandler& operator=(HotkeyHandler&&) noexcept = delete;
};
