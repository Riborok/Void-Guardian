#include "../../include/element/Element.hpp"

Element::Element(Polygon *polygon, SimpleSprite *sprite, const size_t id)
    : Identifiable(id),
      _polygon(polygon),
      _sprite(sprite) { }

Polygon &Element::getPolygon() const {
    return *_polygon;
}

SimpleSprite &Element::getSprite() const {
    return *_sprite;
}

void Element::adjustSpritePosition(const sf::Vector2f &offset) const {
    auto &sprite = getSprite();
    auto &polygon = getPolygon();
    sprite.setPosition(polygon.points()[0] + offset);
}

Element::~Element() noexcept {
    delete _polygon;
    delete _sprite;
}