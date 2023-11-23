#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

#include "Executor.hpp"
#include "../../additionally/other types/QuadtreeEl.hpp"
#include "../../geometry/collision/CollisionManager.hpp"
#include "../input/KeyHandler.hpp"
#include "../player/Player.hpp"

class PlayerExecutor final : public Executor {
    sf::RenderWindow *_window;
    KeyHandler *_key_handler;
    std::vector<Player*> _players;
    CollisionManager *_collision_resolution;
    QuadtreeEl *_quadtree;
public:
    PlayerExecutor(sf::RenderWindow &window, KeyHandler& key_handler, CollisionManager &collision_resolution, QuadtreeEl& quadtree);

    void addPlayer(Player* player);

    void handle(const int delta_time) override;

    ~PlayerExecutor() noexcept override;
    
    PlayerExecutor(PlayerExecutor&&) noexcept = default;
    PlayerExecutor& operator=(PlayerExecutor&&) noexcept = default;
        
    PlayerExecutor(const PlayerExecutor&) noexcept = delete;
    PlayerExecutor& operator=(const PlayerExecutor&) noexcept = delete;
};