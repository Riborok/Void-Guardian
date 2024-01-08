#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

#include "../input/HotkeyManager.hpp"
#include "../processors/game loop/GameLoopState.hpp"

class EventManager final {
    sf::RenderWindow *_window;
    GameLoopState *_game_loop_state;
    SetNewWindowSize _set_new_window_size;
    HotkeyManager _hotkey_manager;
public:
    EventManager(sf::RenderWindow& window, GameLoopState &game_loop_state,
        SetNewWindowSize &&set_new_window_size, FullscreenToggler &fullscreen_toggler,
        const sf::Cursor &cursor, SetPause &&set_pause);

    void processEvents() const;

    ~EventManager() noexcept = default;
    EventManager(const EventManager&) noexcept = delete;
    EventManager& operator=(const EventManager&) noexcept = delete;
    EventManager(EventManager&&) noexcept = delete;
    EventManager& operator=(EventManager&&) noexcept = delete;
};
