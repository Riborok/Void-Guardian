#include "../../include/element/Element.hpp"

#include "../../include/geometry/Trigonometry.hpp"

Element::Element(Polygon *polygon, SimpleSprite *sprite, const sf::Vector2f &scale, const size_t id) :
    Identifiable(id),
    _polygon(polygon),
    _sprite(sprite),
    _transform_params({0, 0}, scale){ }

const Polygon &Element::getPolygon() const {
    return *_polygon;
}

void Element::move(const sf::Vector2f &vector) const {
    _polygon->move(vector);
}

void Element::mirrorHorizontally(const bool is_mirrored) {
    _transform_params.origin.x = is_mirrored ? 0.0f : _sprite->getWidth();
    _transform_params.scale.x = -_transform_params.scale.x;
}

void Element::fillSprite(sf::Sprite &sprite) const {
    
    sprite.setPosition(_polygon->getPoints()[0]);
    sprite.setRotation(Trigonometry::radiansToDegrees(_polygon->getRotation()));
    
    sprite.setOrigin(_transform_params.origin);
    sprite.setScale(_transform_params.scale);
    
    _sprite->setTexture(sprite);
}

Element::~Element() noexcept {
    delete _polygon;
    delete _sprite;
}

bool ElementCompare::operator()(const Element* ptr1, const Element* ptr2) const {
    return *ptr1->_sprite > *ptr2->_sprite;
}