﻿#include <algorithm>
#include "../../../include/geometry/collision/CollisionManager.hpp"
#include "../../../include/game/identifiable/ElementIdTracker.hpp"
#include "../../../include/geometry/collision/CollisionResolution.hpp"

CollisionManager::CollisionManager(CollisionTable type_collision): _type_collision(std::move(type_collision)) { }

bool CollisionManager::processCollisionSet(const Element &element, const CollisionTable::AvailableCollisions& available_collisions,
        const ElementCollisionSet &element_collision_set) {
    bool result = false;
    CollisionResult collision_result;
    const auto& polygon = element.getPolygon();
    for (auto *collision : element_collision_set) {
        const ElementType collision_type = ElementIdTracker::extractType(collision->getId());
        if (available_collisions.find(collision_type) != available_collisions.end() &&
                CollisionDetection::getCollisionResult(polygon, collision->getPolygon(), collision_result)) {
            result = true;
            CollisionResolution::separateElement(element, collision_result);
        }
    }
    return result;
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

bool CollisionManager::hasCollisions(const CollisionTable::AvailableCollisions& available_collisions,
        const ElementCollisionSet& element_collision_set) {
    return std::any_of(element_collision_set.begin(), element_collision_set.end(), [&](const auto *collision) {
        return available_collisions.find(ElementIdTracker::extractType(collision->getId())) != available_collisions.end();
    });
}

bool CollisionManager::hasCollisions(const Element& element, const QuadtreeEl& quadtree) const {
    if (const auto* available_collisions = _type_collision[ElementIdTracker::extractType(element.getId())]) {
        ElementCollisionSet element_collision_set;
        quadtree.fillCollisionSet(element.getPolygon(), element_collision_set);
        return hasCollisions(*available_collisions, element_collision_set);
    }
    return false;
}

bool CollisionManager::processCollisions(const Element &element, const ElementCollisionSet &element_collision_set) const {
    if (const auto* available_collisions = _type_collision[ElementIdTracker::extractType(element.getId())])
        return processCollisionSet(element, *available_collisions, element_collision_set);
    return false;
}

bool CollisionManager::processCollisions(const Element& element, const QuadtreeEl &quadtree) const {
    if (const auto* available_collisions = _type_collision[ElementIdTracker::extractType(element.getId())]) {
        ElementCollisionSet element_collision_set;
        quadtree.fillCollisionSet(element.getPolygon(), element_collision_set);
        return processCollisionSet(element, *available_collisions, element_collision_set);
    }
    return false;
}