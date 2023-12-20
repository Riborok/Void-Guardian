#pragma once
#include <utility>
#include "GameField.hpp"
#include "../geometry/collision/CollisionManager.hpp"
#include "entity/component/gun/GunManager.hpp"
#include "managers/AnimationManager.hpp"
#include "managers/CollectibleManager.hpp"

struct GameSystem final {
    GameField game_field;
    CollisionManager collision_manager;
    AnimationManager animation_manager;
    GunManager gun_manager;
    CollectibleManager collectible_manager;
    GameSystem(GameField&& gm, const CollisionTable &tc, const EntityCreator &ec, GameState &game_state):
        game_field(std::move(gm)),
        collision_manager(tc),
        animation_manager(game_field.quadtree_el),
        gun_manager(ec, collision_manager, game_field.quadtree_el),
        collectible_manager(gun_manager, game_field.quadtree_loc, game_state){}
};