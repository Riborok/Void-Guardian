#pragma once

#include "CollisionTable.hpp"
#include "ElementCollisionSet.hpp"
#include "../../game/entity/FightingEntity.hpp"
#include "../../model/line/Line.hpp"
#include "../../quadtree/quadtree type defs/QuadtreeEl.hpp"

class CollisionHandler final {
    CollisionTable _type_collision;
    static void filterCollisions(const CollisionTable::AvailableCollisions& available_collisions, ElementCollisionSet &result);
    static bool hasCollisions(const CollisionTable::AvailableCollisions& available_collisions, const ElementCollisionSet &element_collision_set);
    static bool handleCollisionSet(const Element &element, const CollisionTable::AvailableCollisions& available_collisions,
                                    const ElementCollisionSet &element_collision_set);
public:
    explicit CollisionHandler(CollisionTable type_collision);

    void fillCollisionSet(const Element &element, const QuadtreeEl &quadtree, ElementCollisionSet &result) const;
    [[nodiscard]] bool hasCollisions(const Element &element, const QuadtreeEl &quadtree) const;
    bool handleCollisions(const Element &element, const ElementCollisionSet &element_collision_set) const;
    bool handleCollisions(const Element &element, const QuadtreeEl &quadtree) const;

    bool isVisible(const Line &line, const FightingEntity &watcher, const FightingEntity &target, const QuadtreeEl &quadtree) const;
    
    ~CollisionHandler() noexcept = default;
    CollisionHandler(CollisionHandler&&) noexcept = default;
    CollisionHandler& operator=(CollisionHandler&&) noexcept = delete;
    CollisionHandler(const CollisionHandler&) noexcept = delete;
    CollisionHandler& operator=(const CollisionHandler&) noexcept = delete;
};