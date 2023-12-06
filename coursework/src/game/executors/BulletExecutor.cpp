#include "../../../include/game/executors/BulletExecutor.hpp"

#include "../../../include/additionally/AdditionalFunc.hpp"
#include "../../../include/geometry/GeomAuxiliaryFunc.hpp"

BulletExecutor::BulletExecutor(CollisionManager &collision_manager, BulletMap &bullet_map,
                               QuadtreeEl& quadtree, EntityDamageManager &&entity_damage_manager):
    _collision_manager(&collision_manager), _bullet_map(&bullet_map),
    _quadtree(&quadtree), _entity_damage_manager(std::move(entity_damage_manager)) { }

void BulletExecutor::evaluateBulletMotion(const Bullet &bullet, const sf::Vector2f &velocity,
        ElementCollisionSet &element_collision_set) const {
    bullet.move(velocity);
    _collision_manager->getCollisions(bullet.getElement(), *_quadtree, element_collision_set);
}

void BulletExecutor::moveBullet(const Bullet& bullet, const int delta_time,
        ElementCollisionSet &element_collision_set) const {
    const sf::Vector2f velocity(bullet.getVelocity(delta_time));
    const sf::Vector2f width_vector(AdditionalFunc::getWidthVector(bullet.getElement()));
    const auto count = static_cast<size_t>(GeomAuxiliaryFunc::calcCoDirectionalScaleFactor(velocity, width_vector));
    for (size_t i = count; i > 0; --i) {
        evaluateBulletMotion(bullet, width_vector, element_collision_set);
        if (!element_collision_set.empty())
            return;
    }
    evaluateBulletMotion(bullet, velocity - width_vector * static_cast<float>(count), element_collision_set);
}

void BulletExecutor::handleBullet(BulletMap::ConstIterator &iterator, const int delta_time) const {
    const auto& bullet = *iterator->second;
    
    const auto& element = bullet.getElement();
    
    ElementCollisionSet element_collision_set;
    _quadtree->remove(&element);
    moveBullet(bullet, delta_time, element_collision_set);

    if (element_collision_set.empty()) {
        _quadtree->insert(&element);
        ++iterator;
    }
    else {
        _entity_damage_manager.applyDamage(bullet.getStats(), element_collision_set);
        _entity_damage_manager.createAnimation(bullet);
        iterator = _bullet_map->erase(&bullet);
    }
}

void BulletExecutor::handle(const int delta_time) {
    for (auto it = _bullet_map->getMap().begin(); it != _bullet_map->getMap().end();) {
        handleBullet(it, delta_time);
    }
}