#pragma once

#include "CollisionTable.hpp"
#include "../../additionally/other types/ElementCollisionSet.hpp"
#include "../../additionally/other types/QuadtreeEl.hpp"

class CollisionManager final {
    CollisionTable _type_collision;
    ElementCollisionSet _element_collision_set;
    
    void processCollisionSet(const Element &element, const AvailableCollisions& available_collisions, const Polygon &polygon) const;
public:
    explicit CollisionManager(CollisionTable &&type_collision);

    void processCollisions(const Element &element, const QuadtreeEl &quadtree);

    ~CollisionManager() noexcept = default;
    
    CollisionManager(const CollisionManager&) noexcept = delete;
    CollisionManager& operator=(const CollisionManager&) noexcept = delete;
    CollisionManager(CollisionManager&&) noexcept = delete;
    CollisionManager& operator=(CollisionManager&&) noexcept = delete;
};
