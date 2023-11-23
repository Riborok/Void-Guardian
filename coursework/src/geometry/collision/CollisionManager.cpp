#include "../../../include/geometry/collision/CollisionManager.hpp"

#include "../../../include/game/identifiable/ElementIdTracker.hpp"
#include "../../../include/geometry/collision/CollisionResolution.hpp"

CollisionManager::CollisionManager(CollisionTable &&type_collision): _type_collision(std::move(type_collision)) { }

void CollisionManager::processCollisionSet(const Element &element, const AvailableCollisions& available_collisions, const Polygon &polygon) const {
    CollisionResult collision_result;
    for (auto *collision : _element_collision_set) {
        const ElementType collision_type = ElementIdTracker::extractType(collision->getId());
        if (available_collisions.find(collision_type) != available_collisions.end() &&
                CollisionDetection::getCollisionResult(polygon, collision->getPolygon(), collision_result))
            CollisionResolution::separateElement(element, collision_result);
    }
}

void CollisionManager::processCollisions(const Element &element, const QuadtreeEl &quadtree) {
    _element_collision_set.clear();
    
    const auto &polygon = element.getPolygon();
    quadtree.getCollisions(polygon, _element_collision_set);

    if (const AvailableCollisions* available_collisions = _type_collision[ElementIdTracker::extractType(element.getId())])
        processCollisionSet(element, *available_collisions, polygon);
}