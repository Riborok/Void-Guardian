#include "../../../include/game/executors/BulletExecutor.hpp"
#include "../../../include/geometry/GeomAuxiliaryFunc.hpp"
#include "../../../include/geometry/SizeUtils.hpp"

BulletExecutor::BulletExecutor(CollisionHandler &collision_handler, BulletMap &bullet_map,
                               QuadtreeEl& quadtree, EntityDamageImpactor &&entity_damage_impactor):
    _collision_handler(&collision_handler), _bullet_map(&bullet_map),
    _quadtree(&quadtree), _entity_damage_impactor(std::move(entity_damage_impactor)) { }

void BulletExecutor::evaluateBulletMotion(const BulletCasing &bullet_casing, const sf::Vector2f &velocity,
        ElementCollisionSet &element_collision_set) const {
    bullet_casing.move(velocity);
    _collision_handler->fillCollisionSet(bullet_casing.getElement(), *_quadtree, element_collision_set);
}

void BulletExecutor::moveBullet(const Bullet& bullet, const int delta_time,
        ElementCollisionSet &element_collision_set) const {
    const auto &bullet_casing = bullet.getBulletCasing();
    const sf::Vector2f velocity(bullet.getVelocity(delta_time));
    const sf::Vector2f width_vector(SizeUtils::getWidthVector(bullet_casing.getElement()));
    const auto count = static_cast<size_t>(GeomAuxiliaryFunc::calcCoDirectionalScaleFactor(velocity, width_vector));
    for (size_t i = count; i > 0; --i) {
        evaluateBulletMotion(bullet_casing, width_vector, element_collision_set);
        if (!element_collision_set.empty())
            return;
    }
    evaluateBulletMotion(bullet_casing, velocity - width_vector * static_cast<float>(count), element_collision_set);
}

void BulletExecutor::handleBullet(BulletMap::ConstIterator &iterator, const int delta_time) const {
    const auto& bullet = *iterator->second;
    
    const auto& element = bullet.getBulletCasing().getElement();
    
    ElementCollisionSet element_collision_set;
    _quadtree->remove(&element);
    moveBullet(bullet, delta_time, element_collision_set);

    if (element_collision_set.empty()) {
        _quadtree->insert(&element);
        ++iterator;
    }
    else {
        _entity_damage_impactor.getDyingAnimator().createAnimation(bullet, (*element_collision_set.begin())->getPolygon());
        _entity_damage_impactor.applyDamage(bullet, element_collision_set);
        delete &element;
        iterator = _bullet_map->erase(&bullet);
    }
}

void BulletExecutor::handle(const int delta_time) {
    for (auto it = _bullet_map->getMap().begin(); it != _bullet_map->getMap().end();) {
        handleBullet(it, delta_time);
    }
}