#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

#include "../WindowParam.hpp"
#include "../input/HotkeyManager.hpp"
#include "../input/InputHandler.hpp"
#include "../processors/game loop/GameLoopState.hpp"

class EventManager final {
    sf::RenderWindow *_window;
    InputHandler *_input_handler;
    GameLoopState *_game_loop_state;
    HotkeyManager *_hotkey_manager;
    WindowParam *_window_param;

    void setNewWindowSize() const;
    void analyzeHotkeyResult(const HotkeyManagerResult result) const;
public:
    EventManager(sf::RenderWindow& window, InputHandler& input_handler, HotkeyManager& hotkey_manager,
                 GameLoopState& game_loop_state, WindowParam& window_param);

    void processEvents() const;

    ~EventManager() noexcept = default;
    
    EventManager(const EventManager&) noexcept = delete;
    EventManager& operator=(const EventManager&) noexcept = delete;
    EventManager(EventManager&&) noexcept = delete;
    EventManager& operator=(EventManager&&) noexcept = delete;
};
