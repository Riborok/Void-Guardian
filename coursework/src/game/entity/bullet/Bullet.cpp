#include "../../../../include/game/entity/bullet/Bullet.hpp"

#include "../../../../include/geometry/GeomAuxiliaryFunc.hpp"

Bullet::Bullet(Element &element, const sf::Vector2f &velocity, const BulletInfo &bullet_info, const EntityInfo &entity_info):
    Entity(entity_info, element), _element(&element),
    _velocity(velocity), _bullet_stats(bullet_info.bullet_stats) {
    GeomAuxiliaryFunc::setLength(_velocity, bullet_info.speed);
}

BulletStats &Bullet::getBulletStats() { return _bullet_stats; }

void Bullet::move(const int delta_time) const { _element->move(_velocity * static_cast<float>(delta_time)); }

void Bullet::appendElements(Elements &elements) const {
    elements.push_back(_element);
}