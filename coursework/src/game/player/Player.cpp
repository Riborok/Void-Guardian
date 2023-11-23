#include "../../../include/game/player/Player.hpp"

#include "../../../include/geometry/Trigonometry.hpp"

Player::Player(ReplaceableElement& element, const Control& control, const float speed)
    : _element(&element), _control(control), _speed(speed), _is_mirrored(false) {}

void Player::mirrorHorizontally() {
    _element->mirrorHorizontally(_is_mirrored);
    _is_mirrored = !_is_mirrored;
}

void Player::checkMirror(const bool is_angle_in_quadrant2_or3) {
    if ((_is_mirrored && !is_angle_in_quadrant2_or3) || (!_is_mirrored && is_angle_in_quadrant2_or3))
        mirrorHorizontally();
}

void Player::move(const sf::Vector2f& destination, const int delta_time) {
    sf::Vector2f direction_vector(destination - _element->getPolygon().calcCenter());
    GeomAuxiliaryFunc::setLength(direction_vector, _speed * static_cast<float>(delta_time));

    checkMirror(Trigonometry::isAngleInQuadrant2Or3(direction_vector));

    _element->move(direction_vector);
}

void Player::setSpriteIndex(const size_t sprite_index) const {
    _element->setSpriteIndex(sprite_index);
}

const Control& Player::getControl() const {
    return _control;
}

const Element& Player::getElement() const {
    return *_element;
}