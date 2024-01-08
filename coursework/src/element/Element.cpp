#include "../../include/element/Element.hpp"

#include "../../include/geometry/Trigonometry.hpp"

Element::Element(Polygon *polygon, SimpleSprite *sprite, const sf::Vector2f &scale, const size_t id) :
    Identifiable(id),
    _polygon(polygon),
    _sprite(sprite),
    _transform_params(
    {isMirrored(scale.x) ? sprite->getWidth() : 0.0f,
            isMirrored(scale.y) ? sprite->getHeight() : 0.0f},
        scale) { }

bool Element::isMirrored(const float coord) {
    return coord < 0;
}

const Polygon &Element::getPolygon() const {
    return *_polygon;
}

const TransformParams &Element::getTransformParams() const {
    return _transform_params;
}

void Element::move(const sf::Vector2f &vector) const {
    _polygon->move(vector);
}

void Element::rotate(const sf::Vector2f &target, const float delta_angle) const {
    _polygon->rotate(target, delta_angle);
}

bool Element::isMirroredHor() const {
    return isMirrored(_transform_params.scale.x);
}

[[nodiscard]] int Element::getZIndex() const { return _sprite->getZIndex(); }

void Element::setZIndex(const int z_index) const { _sprite->setZIndex(z_index); }

void Element::mirrorHor() {
    _transform_params.scale.x = -_transform_params.scale.x;
    _transform_params.origin.x = isMirroredHor() ? _sprite->getWidth() : 0.0f;
}

void Element::fillSprite(sf::Sprite &sprite) const {
    
    sprite.setPosition(_polygon->getPoints()[0]);
    sprite.setRotation(Trigonometry::radiansToDegrees(_polygon->getRotation()));
    
    sprite.setOrigin(_transform_params.origin);
    sprite.setScale(_transform_params.scale);
    
    _sprite->setTextureToSprite(sprite);
}

Element::~Element() noexcept {
    delete _polygon;
    delete _sprite;
}

bool ElementCompare::operator()(const Element* ptr1, const Element* ptr2) const {
    return *ptr1->_sprite > *ptr2->_sprite;
}