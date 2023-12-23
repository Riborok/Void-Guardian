#pragma once

#include "CollisionTable.hpp"
#include "ElementCollisionSet.hpp"
#include "../../game/entity/FightingEntity.hpp"
#include "../../model/line/Line.hpp"
#include "../../quadtree/quadtree type defs/QuadtreeEl.hpp"

class CollisionManager final {
    CollisionTable _type_collision;
    static void filterCollisions(const CollisionTable::AvailableCollisions& available_collisions, ElementCollisionSet &result);
    static bool hasCollisions(const CollisionTable::AvailableCollisions& available_collisions, const ElementCollisionSet &element_collision_set);
    static bool processCollisionSet(const Element &element, const CollisionTable::AvailableCollisions& available_collisions,
                                    const ElementCollisionSet &element_collision_set);
public:
    explicit CollisionManager(CollisionTable type_collision);

    void fillCollisionSet(const Element &element, const QuadtreeEl &quadtree, ElementCollisionSet &result) const;
    [[nodiscard]] bool hasCollisions(const Element &element, const QuadtreeEl &quadtree) const;
    bool processCollisions(const Element &element, const ElementCollisionSet &element_collision_set) const;
    bool processCollisions(const Element &element, const QuadtreeEl &quadtree) const;

    bool isVisible(const Line &line, const FightingEntity &watcher, const FightingEntity &target, const QuadtreeEl &quadtree) const;
    
    ~CollisionManager() noexcept = default;
    CollisionManager(CollisionManager&&) noexcept = default;
    CollisionManager& operator=(CollisionManager&&) noexcept = delete;
    CollisionManager(const CollisionManager&) noexcept = delete;
    CollisionManager& operator=(const CollisionManager&) noexcept = delete;
};
