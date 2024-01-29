#include "../../../../../include/game/entity/component/bullet casing/BulletCasing.hpp"

BulletCasing::BulletCasing(Element& element, const BulletHarm& bullet_harm, const size_t num):
    EntityComponent(num, element.getId()), _element(&element), _bullet_harm(bullet_harm) { }

const BulletHarm& BulletCasing::getBulletHarm() const { return _bullet_harm; }

const Element& BulletCasing::getElement() const { return *_element; }

void BulletCasing::move(const sf::Vector2f& velocity) const { _element->move(velocity); }