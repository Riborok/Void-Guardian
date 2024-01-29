#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

#include "../input/FullscreenToggler.hpp"
#include "../input/HotkeyHandler.hpp"
#include "../game handlers/game loop/GameLoopState.hpp"

class EventHandler final {
    sf::RenderWindow *_window;
    GameLoopState *_game_loop_state;
    SetNewWindowSize _set_new_window_size;
    HotkeyHandler _hotkey_handler;
public:
    EventHandler(sf::RenderWindow& window, GameLoopState &game_loop_state,
        SetNewWindowSize &&set_new_window_size, FullscreenToggler &fullscreen_toggler,
        const sf::Cursor &cursor, SetPause &&set_pause);

    void handleEvents() const;

    ~EventHandler() noexcept = default;
    EventHandler(const EventHandler&) noexcept = delete;
    EventHandler& operator=(const EventHandler&) noexcept = delete;
    EventHandler(EventHandler&&) noexcept = delete;
    EventHandler& operator=(EventHandler&&) noexcept = delete;
};
