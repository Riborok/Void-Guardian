#include "../../../include/geometry/collision/CollisionManager.hpp"

#include "../../../include/game/identifiable/ElementIdTracker.hpp"
#include "../../../include/geometry/collision/CollisionResolution.hpp"

CollisionManager::CollisionManager(CollisionTable &&type_collision): _type_collision(std::move(type_collision)) { }

void CollisionManager::processCollisionSet(const Element &element, const CollisionTable::AvailableCollisions& available_collisions,
        const ElementCollisionSet &element_collision_set) {
    CollisionResult collision_result;
    const auto& polygon = element.getPolygon();
    for (auto *collision : element_collision_set) {
        const ElementType collision_type = ElementIdTracker::extractType(collision->getId());
        if (available_collisions.find(collision_type) != available_collisions.end() &&
                CollisionDetection::getCollisionResult(polygon, collision->getPolygon(), collision_result))
            CollisionResolution::separateElement(element, collision_result);
    }
}

void CollisionManager::filterCollisions(const CollisionTable::AvailableCollisions& available_collisions, ElementCollisionSet &result) {
    for (auto it = result.begin(); it != result.end();) {
        const ElementType collision_type = ElementIdTracker::extractType((*it)->getId());
        if (available_collisions.find(collision_type) == available_collisions.end())
            it = result.erase(it);
        else
            ++it;
    }
}

void CollisionManager::fillCollisionSet(const Element &element, const QuadtreeEl &quadtree, ElementCollisionSet &result) const {
    if (const auto* available_collisions = _type_collision[ElementIdTracker::extractType(element.getId())]) {
        quadtree.fillCollisionSet(element.getPolygon(), result);
        filterCollisions(*available_collisions, result);
    }
}

void CollisionManager::processCollisions(const Element &element, const ElementCollisionSet &element_collision_set) const {
    if (const auto* available_collisions = _type_collision[ElementIdTracker::extractType(element.getId())])
        processCollisionSet(element, *available_collisions, element_collision_set);
}