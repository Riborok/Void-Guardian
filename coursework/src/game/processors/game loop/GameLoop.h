#pragma once
#include "../../managers/EventManager.h"
#include "../Render.h"

class GameLoop final {
    EventManager _event_manager;
    Render _render;
    SpriteDrawer _sprite_drawer;
    GameLoopState _game_loop_state;
public:
    GameLoop(sf::RenderWindow &window, KeyHandler &key_handler, HotkeyManager &hotkey_manager,
            std::unordered_set<Element*, IdentifiableHash> &elements):
        _event_manager(window, key_handler, hotkey_manager, _game_loop_state),
        _sprite_drawer(window, elements) { }
    
    void nextIteration(){
        _event_manager.processEvents();
        if (_game_loop_state.is_active) {
            _render.renderAll(_game_loop_state.clock.restart().asMilliseconds());
            _sprite_drawer.drawAll();
        }
    }
    
    void registerExecutor(Types::Executor *executor) { _render.add(executor); }
    
    ~GameLoop() noexcept = default;
    
    GameLoop(const GameLoop&) noexcept = delete;
    GameLoop& operator=(const GameLoop&) noexcept = delete;
    GameLoop(GameLoop&&) noexcept = delete;
    GameLoop& operator=(GameLoop&&) noexcept = delete;
};
