#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

#include "Executor.hpp"
#include "../../geometry/collision/CollisionManager.hpp"
#include "../input/KeyHandler.hpp"
#include "../entity/player/Player.hpp"

class PlayerExecutor final : public Executor {
    typedef std::vector<Player*> Players;
    
    sf::RenderWindow *_window;
    KeyHandler *_key_handler;
    Players _players;
    CollisionManager *_collision_resolution;
    QuadtreeEl *_quadtree;
    
    void updateWraith(const Wraith &wraith, const Control &control, const int delta_time) const;
    void updateGun(const Gun &gun, const sf::Vector2f &target_p, const float target_a) const;

    void moveWraith(const Wraith &wraith, const sf::Vector2f &vector) const;
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