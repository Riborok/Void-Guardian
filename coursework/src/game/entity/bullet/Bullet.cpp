#include "../../../../include/game/entity/bullet/Bullet.hpp"

#include "../../../../include/geometry/GeomAuxiliaryFunc.hpp"

Bullet::Bullet(Element &element, const sf::Vector2f &velocity, const BulletInfo &bullet_info, const EntityInfo &entity_info):
    Entity(entity_info, element), _element(&element),
    _velocity(velocity), _bullet_stats(static_cast<BulletStats>(bullet_info)) {
    GeomAuxiliaryFunc::setLength(_velocity, bullet_info.speed);
}

BulletStats &Bullet::getBulletStats() { return _bullet_stats; }

void Bullet::move(const int delta_time) const { _element->move(_velocity * static_cast<float>(delta_time)); }

const Element& Bullet::getElement() const { return *_element; }