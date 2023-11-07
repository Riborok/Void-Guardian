#include "../../../../include/game/processors/game loop/GameLoop.hpp"

GameLoop::GameLoop(sf::RenderWindow& window, KeyHandler& key_handler, HotkeyManager& hotkey_manager,
    std::unordered_set<Element*, IdentifiableHash>& elements, sf::Vector2f& window_half_size, sf::Vector2f& offset)
    : _event_manager(window, key_handler, hotkey_manager, _game_loop_state, window_half_size),
    _sprite_adjuster(elements, offset),
    _sprite_drawer(window, elements) { }

void GameLoop::nextIteration() {
    _event_manager.processEvents();
    if (_game_loop_state.is_active) {
        _sprite_adjuster.adjustPositions();
        _render.renderAll(_game_loop_state.clock.restart().asMilliseconds());
        _sprite_drawer.drawAll();
    }
}

void GameLoop::registerExecutor(Types::Executor* executor) {
    _render.add(executor);
}