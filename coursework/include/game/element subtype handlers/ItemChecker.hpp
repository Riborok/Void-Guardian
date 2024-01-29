#pragma once
#include "../GameState.hpp"
#include "../../geometry/collision/ElementCollisionSet.hpp"
#include "../../quadtree/quadtree type defs/QuadtreeLoc.hpp"
#include "../entity/component/gun/GunInstaller.hpp"

class ItemChecker final {
    GunInstaller *_gun_installer;
    const QuadtreeLoc *_quadtree_loc;
    GameState *_game_state;

    void handleSelection(Player &player, const Element &element) const;
public:
    ItemChecker(GunInstaller &gun_installer, const QuadtreeLoc &quadtree_loc, GameState &game_state);
    void checkTakingItem(Player &player, const ElementCollisionSet &collision_set) const;

    ~ItemChecker() noexcept = default;
    ItemChecker(ItemChecker&&) noexcept = default;
    ItemChecker& operator=(ItemChecker&&) noexcept = delete;
    ItemChecker(const ItemChecker&) noexcept = delete;
    ItemChecker& operator=(const ItemChecker&) noexcept = delete;
};