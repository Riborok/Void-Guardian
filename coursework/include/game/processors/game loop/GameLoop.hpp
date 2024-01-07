#pragma once
#include "../GameUpdater.hpp"
#include "../../managers/EventManager.hpp"
#include "../Render.hpp"
#include "../SpriteDrawer.hpp"
#include "../../executors/Executor.hpp"

class GameLoop final {
    GameLoopState _game_loop_state;
    EventManager _event_manager;
    Render _render;
    SpriteDrawer _sprite_drawer;
    GameUpdater *_game_updater;
public:
    GameLoop(sf::RenderWindow& window, HotkeyManager& hotkey_manager,
        GameUpdater &game_updater, FightingMaps &fighting_maps, const std::string &health_font_src);

    void nextIteration();

    void registerExecutor(Executor* executor);

    ~GameLoop() noexcept = default;

    GameLoop(const GameLoop&) noexcept = delete;
    GameLoop& operator=(const GameLoop&) noexcept = delete;
    GameLoop(GameLoop&&) noexcept = delete;
    GameLoop& operator=(GameLoop&&) noexcept = delete;
};
