#pragma once
#include "../../managers/EventManager.h"
#include "../Render.h"
#include "../SpriteAdjuster.h"

class GameLoop final {
    GameLoopState _game_loop_state;
    
    EventManager _event_manager;
    
    Render _render;
    SpriteAdjuster _sprite_adjuster;
    SpriteDrawer _sprite_drawer;
public:
    GameLoop(sf::RenderWindow &window, KeyHandler &key_handler, HotkeyManager &hotkey_manager,
            std::unordered_set<Element*, IdentifiableHash> &elements):
        _event_manager(window, key_handler, hotkey_manager, _game_loop_state),
        _sprite_adjuster(window, elements),
        _sprite_drawer(window, elements){ }
    
    void nextIteration(){
        _event_manager.processEvents();
        if (_game_loop_state.is_active) {
            _render.renderAll(_game_loop_state.clock.restart().asMilliseconds());
            _sprite_adjuster.adjustPositions();
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
