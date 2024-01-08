#include "../../../../include/game/processors/game loop/GameLoop.hpp"

#include "../../../../include/game/processors/StateChangerForAnimated.hpp"

GameLoop::GameLoop(SetNewWindowSize &&set_new_window_size, sf::RenderWindow& window,
        FullscreenToggler &fullscreen_toggler, PauseSubset &pause_subset, GameState &game_state,
        GameUpdater &game_updater, FightingMaps &fighting_maps, const std::string &health_font_src):
    _event_manager(window, _game_loop_state, std::move(set_new_window_size), fullscreen_toggler, pause_subset.cursor,
                   FunctionCreator::createSetPause(pause_subset, game_state, _game_loop_state.clock, window)),
    _sprite_drawer(window, {window, fighting_maps, health_font_src}), _game_updater(&game_updater) { }

void GameLoop::nextIteration() {
    if (_game_loop_state.is_active) {
        const auto delta_time(_game_loop_state.clock.restart().asMilliseconds());
        _render.renderAll(delta_time);
        _game_updater->updateView();
        
        ElementCollisionSet element_collision_set;
        _game_updater->fillCollisionSet(element_collision_set);
        StateChangerForAnimated::change(element_collision_set, delta_time);
        _sprite_drawer.drawAll(element_collision_set);
    }
    _event_manager.processEvents();
}

void GameLoop::registerExecutor(Executor* executor) {
    _render.add(executor);
}