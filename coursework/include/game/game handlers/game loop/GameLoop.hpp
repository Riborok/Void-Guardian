#pragma once
#include "GameLoopState.hpp"
#include "../GameUpdater.hpp"
#include "../../game handlers/EventHandler.hpp"
#include "../Render.hpp"
#include "../SpriteDrawer.hpp"
#include "../../PauseSubset.hpp"
#include "../../executors/Executor.hpp"

class GameLoop final {
    GameLoopState _game_loop_state;
    EventHandler _event_handler;
    Render _render;
    SpriteDrawer _sprite_drawer;
    GameUpdater *_game_updater;
public:
    GameLoop(SetNewWindowSize &&set_new_window_size,sf::RenderWindow& window, FullscreenToggler &fullscreen_toggler,
        PauseSubset &pause_subset, GameState &game_state, GameUpdater &game_updater,
        FightingMaps &fighting_maps, const std::string &health_font_src);

    void nextIteration();
    void registerExecutor(Executor* executor);

    ~GameLoop() noexcept = default;
    GameLoop(const GameLoop&) noexcept = delete;
    GameLoop& operator=(const GameLoop&) noexcept = delete;
    GameLoop(GameLoop&&) noexcept = delete;
    GameLoop& operator=(GameLoop&&) noexcept = delete;
};
