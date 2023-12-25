#pragma once
#include <SFML/Window/Keyboard.hpp>

#include "FullscreenToggler.hpp"
#include "../GameState.hpp"

enum class HotkeyManagerResult final {
    NONE,
    TOGGLE_FULLSCREEN,
    RETURN_TO_MENU,
};

class HotkeyManager final {
    FullscreenToggler *_fullscreen_toggler;
    GameState *_game_state;
public:
    explicit HotkeyManager(FullscreenToggler &fullscreen_toggler, GameState &game_state);
    [[nodiscard]] HotkeyManagerResult handleHotkeys(const sf::Keyboard::Key key_code) const;
    
    ~HotkeyManager() noexcept = default;
    
    HotkeyManager(const HotkeyManager&) noexcept = delete;
    HotkeyManager& operator=(const HotkeyManager&) noexcept = delete;
    HotkeyManager(HotkeyManager&&) noexcept = delete;
    HotkeyManager& operator=(HotkeyManager&&) noexcept = delete;
};
