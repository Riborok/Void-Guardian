#include "../../../../../include/game/entity/component/bullet casing/BulletCasing.hpp"

BulletCasing::BulletCasing(Element& element, const BulletStats& stats, const size_t num):
    EntityComponent(num, element.getId()), _element(&element), _stats(stats) { }

const BulletStats& BulletCasing::getStats() const { return _stats; }

const Element& BulletCasing::getElement() const { return *_element; }

void BulletCasing::move(const sf::Vector2f& velocity) const { _element->move(velocity); }