#include "../../include/element/Element.hpp"

Element::Element(Polygon *polygon, SimpleSprite *sprite, const size_t id)
    : Identifiable(id),
      _polygon(polygon),
      _sprite(sprite) { }

const Polygon &Element::getPolygon() const {
    return *_polygon;
}

const SimpleSprite &Element::getSprite() const {
    return *_sprite;
}

void Element::move(const sf::Vector2f &vector) const {
    _polygon->move(vector);
    _sprite->move(vector);
}

void Element::mirrorHorizontally(const bool is_mirrored) const {
    _sprite->setOrigin(is_mirrored ? 0.0f : static_cast<float>(_sprite->getTextureRect().width), 0.0f);
    _sprite->setScale(-_sprite->getScale().x, _sprite->getScale().y);
}

Element::~Element() noexcept {
    delete _polygon;
    delete _sprite;
}