#include "../../../../include/game/entity/bullet/Bullet.hpp"

#include "../../../../include/geometry/GeomAuxiliaryFunc.hpp"

Bullet::Bullet(Element &element, const sf::Vector2f &velocity, const BulletInfo &bullet_info,
        const EntityInfo &entity_info, const int num):
    Entity(entity_info, element), _element(&element),
    _velocity(velocity), _bullet_stats(bullet_info.bullet_stats), _num(num) {
    GeomAuxiliaryFunc::setLength(_velocity, bullet_info.speed);
}

const BulletStats &Bullet::getStats() const { return _bullet_stats; }

int Bullet::getNum() const { return _num; }

const Element& Bullet::getElement() const { return *_element; }

void Bullet::move(const int delta_time) const { _element->move(_velocity * static_cast<float>(delta_time)); }