#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

#include "../input/HotkeyManager.hpp"
#include "../input/KeyHandler.hpp"
#include "../processors/game loop/GameLoopState.hpp"

class EventManager final {
    sf::RenderWindow* _window;
    KeyHandler* _key_handler;
    GameLoopState* _game_loop_state;
    HotkeyManager* _hotkey_manager;
    sf::Vector2f* _window_half_size;

    void setNewWindowSize() const;
    void analyzeHotkeyResult(const HotkeyManagerResult result) const;
public:
    EventManager(sf::RenderWindow& window, KeyHandler& key_handler, HotkeyManager& hotkey_manager,
                 GameLoopState& game_loop_state, sf::Vector2f& window_half_size);

    void processEvents() const;

    ~EventManager() noexcept = default;
    
    EventManager(const EventManager&) noexcept = delete;
    EventManager& operator=(const EventManager&) noexcept = delete;
    EventManager(EventManager&&) noexcept = delete;
    EventManager& operator=(EventManager&&) noexcept = delete;
};
