#include "../../../include/game/player/Player.hpp"

#include "../../../include/geometry/Trigonometry.hpp"
#include "../../../include/model/polygon/ManipulationOfPolygon.hpp"

Player::Player(ReplaceableElement& element, const Types::Control& control, const float speed)
    : _element(&element), _control(control), _speed(speed), _is_mirrored(false) {}

void Player::restoreMirror() {
    auto& sprite = _element->getSprite();
    sprite.setOrigin(0.0f, 0.0f);
    sprite.setScale(-sprite.getScale().x, sprite.getScale().y);
    _is_mirrored = false;
}

void Player::mirrorHorizontally() {
    auto& sprite = _element->getSprite();
    sprite.setOrigin(static_cast<float>(sprite.getTextureRect().width), 0.0f);
    sprite.setScale(-sprite.getScale().x, sprite.getScale().y);
    _is_mirrored = true;
}

void Player::checkMirror(const bool is_angle_in_quadrant2_or3) {
    if (_is_mirrored) {
        if (!is_angle_in_quadrant2_or3)
            restoreMirror();
    } else {
        if (is_angle_in_quadrant2_or3)
            mirrorHorizontally();
    }
}

sf::Vector2f Player::calcCenter() const {
    const auto& polygon = _element->getPolygon();
    const auto& position = _element->getSprite().getPosition();
    return {position.x + polygon.getBoundingRectangleHeight() / 2, position.y + polygon.getBoundingRectangleHeight() / 2};
}

void Player::move(const sf::Vector2f& destination, const int delta_time) {
    sf::Vector2f direction_vector = destination - calcCenter();
    GeomAuxiliaryFunc::setLength(direction_vector, _speed * static_cast<float>(delta_time));

    checkMirror(Trigonometry::isAngleInQuadrant2Or3(direction_vector));

    ManipulationOfPolygon::movePolygon(_element->getPolygon(), direction_vector);
}

void Player::setSpriteIndex(const size_t sprite_index) const {
    _element->setSpriteIndex(sprite_index);
}

const Types::Control& Player::getControl() const {
    return _control;
}

Element& Player::getElement() const {
    return *_element;
}