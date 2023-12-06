#include "../../../../include/game/entity/bullet/BulletCreator.hpp"

#include "../../../../include/additionally/AdditionalFunc.hpp"
#include "../../../../include/geometry/GeomAuxiliaryFunc.hpp"
#include "../../../../include/geometry/collision/CollisionDetection.hpp"
#include "../../../../include/geometry/collision/CollisionResolution.hpp"

BulletCreator::BulletCreator(BulletMap &bullet_map, EntityCreator &entity_creator, QuadtreeEl &quadtree_el):
    _bullet_map(&bullet_map), _entity_creator(&entity_creator), _quadtree_el(&quadtree_el) {}

float BulletCreator::getOverlap(const Element &bullet_element, const Element &character_bullet_collision,
        const sf::Vector2f &collision_normal) {
    Projection projection1;
    CollisionDetection::getProjection(bullet_element.getPolygon(), collision_normal, projection1);

    Projection projection2;
    CollisionDetection::getProjection(character_bullet_collision.getPolygon(), collision_normal, projection2);
    
    return projection1.min - projection2.max;
}

void BulletCreator::processEstimatedCollision(const Element &bullet_element,
        const Element &character_bullet_collision) {
    auto collision_normal(AdditionalFunc::getWidthVector(bullet_element));
    GeomAuxiliaryFunc::normalize(collision_normal);

    if (const float overlap = getOverlap(bullet_element, character_bullet_collision, collision_normal); overlap < 0)
        CollisionResolution::separateElement(bullet_element, collision_normal, overlap);
}

void BulletCreator::spawnBullet(const LaunchData &launch_data, const Element &character_bullet_collision) const {
    auto* bullet = _entity_creator->createBullet(launch_data);
    processEstimatedCollision(bullet->getElement(), character_bullet_collision);
    _bullet_map->insert(bullet);
    _quadtree_el->insert(&bullet->getElement());
}
