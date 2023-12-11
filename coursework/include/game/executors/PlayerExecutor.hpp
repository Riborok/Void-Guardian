#pragma once

#include "Executor.hpp"
#include "../../geometry/collision/CollisionManager.hpp"
#include "../entity/bullet/BulletCreator.hpp"
#include "../input/InputHandler.hpp"
#include "../entity/player/Player.hpp"
#include "../entity/player/PlayerMap.hpp"
#include "../input/MouseLocator.hpp"
#include "../managers/CollectibleManager.hpp"

class PlayerExecutor final : public Executor {
    MouseLocator _mouse_locator;
    BulletCreator _bullet_creator;
    InputHandler *_input_handler;
    CollisionManager *_collision_manager;
    CollectibleManager *_collectible_manager;
    PlayerMap *_player_map;
    QuadtreeEl *_quadtree;

    struct Action final {
        bool has_movement;
        bool has_selection;
        [[nodiscard]] bool hasAnyAction() const { return has_movement || has_selection; }
        Action(const bool has_movement, const bool has_selection):
            has_movement(has_movement), has_selection(has_selection) {}
    };
    [[nodiscard]] bool checkMovement(const Player &player, const int delta_time, sf::Vector2f &result) const;
    [[nodiscard]] bool checkSelection(const Player &player) const;
    
    void updatePlayer(Player &player, const int delta_time) const;
    void processActions(Player &player, const Action &action, const sf::Vector2f &movement_vector) const;
    void movePlayer(const Element &element, const sf::Vector2f &movement_vector, ElementCollisionSet &element_collision_set) const;
    
    void updateGun(const Gun &gun, const sf::Vector2f &target_p, const float target_a) const;
    void checkShoot(const Player &player) const;
public:
    PlayerExecutor(MouseLocator &&mouse_locator, BulletCreator &&bullet_creator, InputHandler& input_handler,
        CollisionManager &collision_manager, CollectibleManager &collectible_manager,
        PlayerMap &player_map, QuadtreeEl &quadtree);
    void handle(const int delta_time) override;

    ~PlayerExecutor() noexcept override = default;
    PlayerExecutor(PlayerExecutor&&) noexcept = default;
    PlayerExecutor& operator=(PlayerExecutor&&) noexcept = default;
    PlayerExecutor(const PlayerExecutor&) noexcept = delete;
    PlayerExecutor& operator=(const PlayerExecutor&) noexcept = delete;
};
