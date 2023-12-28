#include "../../../../include/game/processors/game loop/GameLoop.hpp"

#include "../../../../include/game/processors/StateChangerForAnimated.hpp"

GameLoop::GameLoop(sf::RenderWindow& window, InputHandler& input_handler, HotkeyManager& hotkey_manager,
        GameUpdater &game_updater, FightingMaps &fighting_maps, const std::string &health_font_src)
    : _event_manager(window, input_handler, hotkey_manager, _game_loop_state, game_updater.getWindowParam()),
    _sprite_drawer(window, {window, fighting_maps, health_font_src}), _game_updater(&game_updater) { }

void GameLoop::nextIteration() {
    _event_manager.processEvents();
    if (_game_loop_state.is_active) {
        const auto delta_time(_game_loop_state.clock.restart().asMilliseconds());
        _render.renderAll(delta_time);
        _game_updater->updateView();
        
        ElementCollisionSet element_collision_set;
        _game_updater->fillCollisionSet(element_collision_set);
        StateChangerForAnimated::change(element_collision_set, delta_time);
        _sprite_drawer.drawAll(element_collision_set);
    }
}

void GameLoop::registerExecutor(Executor* executor) {
    _render.add(executor);
}