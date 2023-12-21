#include "../../../../include/game/entity/bullet/Bullet.hpp"

#include "../../../../include/geometry/GeomAuxiliaryFunc.hpp"

Bullet::Bullet(BulletCasing &&bullet_casing, const sf::Vector2f &velocity, const EntityInfo &entity_info):
    Entity(entity_info, bullet_casing.getElement().getId()), _velocity(velocity), _bullet_casing(std::move(bullet_casing)) { }

sf::Vector2f Bullet::getVelocity(const int delta_time) const { return _velocity * static_cast<float>(delta_time); }

const BulletCasing& Bullet::getBulletCasing() const { return _bullet_casing; }