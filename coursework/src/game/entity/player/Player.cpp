﻿#include "../../../../include/game/entity/player/Player.hpp"

Player::Player(Wraith&& wraith, Gun &&gun, const EntityInfo &entity_info, const Control &control) :
    Entity(entity_info, wraith.getElement()), _wraith(std::move(wraith)), _gun(std::move(gun)), _control(control) { }

const Control& Player::getControl() const { return _control; }

sf::Vector2f Player::getGunPos() const {
    auto result(_wraith.getElement().getPolygon().calcCenter());
    result.x += _gun.getElement().isMirroredHor() ? -GUN_POS_INDENT_X : GUN_POS_INDENT_X;
    result.y += GUN_POS_INDENT_Y;
    return result;
}

const Wraith &Player::getWraith() const { return _wraith; }
const Gun &Player::getGun() const { return _gun; }

void Player::checkMirror(const bool is_angle_in_quadrant2_or3) const {
    const bool is_mirrored = _wraith.getElement().isMirroredHor();
    if ((is_mirrored && !is_angle_in_quadrant2_or3) || (!is_mirrored && is_angle_in_quadrant2_or3)) {
        _wraith._element->mirrorHor();
        _gun._element->mirrorHor();
    }
}
