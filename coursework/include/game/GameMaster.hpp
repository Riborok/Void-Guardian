#pragma once

#include <unordered_set>
#include "construction/Location.hpp"
#include "executors/PlayerExecutor.hpp"
#include "executors/SpriteStateExecutor.hpp"
#include "input/KeyHandler.hpp"
#include "processors/game loop/GameLoop.hpp"

class GameMaster final {
    static constexpr float QUADTREE_SIZE = 3840;

    sf::RenderWindow *_window;
    std::unordered_set<Element*, IdentifiableHash> _elements;
    HotkeyManager _hotkey_manager;
    KeyHandler _key_handler;
    Quadtree<Element> _quadtree;
    Quadtree<Location> _locations;
    GameLoop _game_loop;

    Polygon *_focus;
    sf::Vector2f _window_half_size;
    sf::Vector2f _offset;

    void setParameters();

public:
    void addPlayer(PlayerExecutor *player_executor);
    explicit GameMaster(sf::RenderWindow &window);
    void start();
    
    ~GameMaster() noexcept = default;
    
    GameMaster(const GameMaster&) noexcept = delete;
    GameMaster& operator=(const GameMaster&) noexcept = delete;
    GameMaster(GameMaster&&) noexcept = delete;
    GameMaster& operator=(GameMaster&&) noexcept = delete;
};