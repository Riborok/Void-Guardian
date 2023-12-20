#pragma once
#include "../GameState.hpp"
#include "../../geometry/collision/ElementCollisionSet.hpp"
#include "../../quadtree/quadtree type defs/QuadtreeLoc.hpp"
#include "../entity/component/gun/GunManager.hpp"

class CollectibleManager final {
    GunManager *_gun_manager;
    const QuadtreeLoc *_quadtree_loc;
    GameState *_game_state;

    void processSelection(Player &player, const Element &element) const;
public:
    CollectibleManager(GunManager &gun_manager, const QuadtreeLoc &quadtree_loc, GameState &game_state);
    void checkCollectibleSelection(Player &player, const ElementCollisionSet &collision_set) const;

    ~CollectibleManager() noexcept = default;
    CollectibleManager(CollectibleManager&&) noexcept = default;
    CollectibleManager& operator=(CollectibleManager&&) noexcept = delete;
    CollectibleManager(const CollectibleManager&) noexcept = delete;
    CollectibleManager& operator=(const CollectibleManager&) noexcept = delete;
};
