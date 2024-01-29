#pragma once
#include <utility>
#include "GameField.hpp"
#include "../geometry/collision/CollisionHandler.hpp"
#include "entity/component/gun/GunInstaller.hpp"
#include "element subtype handlers/AnimationAttacher.hpp"
#include "element subtype handlers/ItemChecker.hpp"

struct GameSystem final {
    GameField game_field;
    CollisionHandler collision_handler;
    AnimationAttacher animation_attacher;
    GunInstaller gun_installer;
    ItemChecker item_handler;
    GameSystem(GameField&& gm, const CollisionTable &tc, const EntityCreator &ec, GameState &game_state):
        game_field(std::move(gm)),
        collision_handler(tc),
        animation_attacher(game_field.quadtree_el),
        gun_installer(ec, collision_handler, game_field.quadtree_el),
        item_handler(gun_installer, game_field.quadtree_loc, game_state){}
};