#include "../../../../include/game/processors/game loop/GameLoop.hpp"

GameLoop::GameLoop(sf::RenderWindow& window, KeyHandler& key_handler, HotkeyManager& hotkey_manager, GameUpdater &game_updater)
    : _event_manager(window, key_handler, hotkey_manager, _game_loop_state, game_updater.getWindowParam()),
    _sprite_drawer(window, game_updater.getCollidedElements()), _game_updater(&game_updater) { }

void GameLoop::nextIteration() {
    _event_manager.processEvents();
    if (_game_loop_state.is_active) {
        _render.renderAll(_game_loop_state.clock.restart().asMilliseconds());
        _game_updater->update();
        _sprite_drawer.drawAll();
    }
}

void GameLoop::registerExecutor(Executor* executor) {
    _render.add(executor);
}