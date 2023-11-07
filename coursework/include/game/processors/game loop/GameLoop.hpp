#pragma once
#include "../../managers/EventManager.hpp"
#include "../Render.hpp"
#include "../SpriteAdjuster.hpp"
#include "../SpriteDrawer.hpp"

class GameLoop {
    GameLoopState _game_loop_state;
    EventManager _event_manager;
    Render _render;
    SpriteAdjuster _sprite_adjuster;
    SpriteDrawer _sprite_drawer;
public:
    GameLoop(sf::RenderWindow& window, KeyHandler& key_handler, HotkeyManager& hotkey_manager,
        std::unordered_set<Element*, IdentifiableHash>& elements, sf::Vector2f& window_half_size, sf::Vector2f& offset);

    void nextIteration();

    void registerExecutor(Types::Executor* executor);

    ~GameLoop() noexcept = default;

    GameLoop(const GameLoop&) = delete;
    GameLoop& operator=(const GameLoop&) = delete;
    GameLoop(GameLoop&&) = delete;
    GameLoop& operator=(GameLoop&&) = delete;
};
