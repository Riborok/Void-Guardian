#include "../../../../include/game/entity/player/Player.hpp"

Player::Player(Wraith&& wraith, Gun &&gun, const EntityInfo &entity_info, const Control &control) :
    Entity(entity_info, wraith.getElement()), _wraith(std::move(wraith)), _gun(std::move(gun)), _control(control) { }

const Control& Player::getControl() const { return _control; }

sf::Vector2f Player::getGunPos() const {
    auto result(_wraith.getElement().getPolygon().calcCenter());
    result.x += _gun.isMirror() ? -GUN_POS_INDENT_X : GUN_POS_INDENT_X;
    result.y += GUN_POS_INDENT_Y;
    return result;
}

const Wraith &Player::getWraith() const { return _wraith; }
const Gun &Player::getGun() const { return _gun; }

void Player::checkMirror(const bool is_angle_in_quadrant2_or3) {
    _wraith.checkMirror(is_angle_in_quadrant2_or3);
    _gun.checkMirror(is_angle_in_quadrant2_or3);
}