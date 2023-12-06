#pragma once

#include "Executor.hpp"
#include "../../geometry/collision/CollisionManager.hpp"
#include "../entity/bullet/BulletCreator.hpp"
#include "../input/InputHandler.hpp"
#include "../entity/player/Player.hpp"
#include "../entity/player/PlayerMap.hpp"
#include "../input/MouseLocator.hpp"

class PlayerExecutor final : public Executor {
    MouseLocator _mouse_locator;
    BulletCreator _bullet_creator;
    InputHandler *_input_handler;
    CollisionManager *_collision_manager;
    PlayerMap *_player_map;
    QuadtreeEl *_quadtree;
    
    void updateWraith(const Wraith &wraith, const Control &control, const int delta_time) const;
    void updateGun(const Gun &gun, const sf::Vector2f &target_p, const float target_a) const;
    void checkShoot(const Player &player) const;
    
    void moveWraith(const Wraith &wraith, const sf::Vector2f &vector) const;
public:
    PlayerExecutor(MouseLocator &&mouse_locator, BulletCreator &&bullet_creator, InputHandler& input_handler,
        CollisionManager &collision_manager, PlayerMap &player_map, QuadtreeEl& quadtree);
    void handle(const int delta_time) override;

    ~PlayerExecutor() noexcept override = default;
    PlayerExecutor(PlayerExecutor&&) noexcept = default;
    PlayerExecutor& operator=(PlayerExecutor&&) noexcept = default;
    PlayerExecutor(const PlayerExecutor&) noexcept = delete;
    PlayerExecutor& operator=(const PlayerExecutor&) noexcept = delete;
};
