#pragma once

#include "CollisionTable.hpp"
#include "ElementCollisionSet.hpp"
#include "../../quadtree/quadtree type defs/QuadtreeEl.hpp"

class CollisionManager final {
    CollisionTable _type_collision;
    static void filterCollisions(const CollisionTable::AvailableCollisions& available_collisions, ElementCollisionSet &result);
    static void processCollisionSet(const Element &element, const CollisionTable::AvailableCollisions& available_collisions,
                                    const ElementCollisionSet &element_collision_set);
public:
    explicit CollisionManager(CollisionTable &&type_collision);

    void fillCollisionSet(const Element &element, const QuadtreeEl &quadtree, ElementCollisionSet &result) const;
    void processCollisions(const Element &element, const ElementCollisionSet &element_collision_set) const;

    ~CollisionManager() noexcept = default;
    
    CollisionManager(const CollisionManager&) noexcept = delete;
    CollisionManager& operator=(const CollisionManager&) noexcept = delete;
    CollisionManager(CollisionManager&&) noexcept = delete;
    CollisionManager& operator=(CollisionManager&&) noexcept = delete;
};
