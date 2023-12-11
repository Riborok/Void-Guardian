#include "../../../../include/game/entity/player/Player.hpp"

Player::Player(Wraith&& wraith, Gun &&gun, const EntityInfo &entity_info, const Control &control) :
    Entity(entity_info, wraith.getElement()), _wraith(std::move(wraith)), _gun(std::move(gun)), _control(control) {
    _gun.getElement().setZIndex(_wraith.getElement().getZIndex() + 1);
}

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
        _wraith.getElement().mirrorHor();
        _gun.getElement().mirrorHor();
    }
}

bool Player::canTakeNewGun() const {
    if (_last_change_elapsed_time.getElapsedTime().asMilliseconds() >= GUN_CHANGE_COOLDOWN) {
        _last_change_elapsed_time.restart();
        return true;
    }
    return false;
}

Gun Player::takeNewGun(Gun&& gun) {
    const float angle = _gun.getElement().getPolygon().getRotation();
    Gun result = std::move(_gun);
    
    _gun = std::move(gun);
    _gun.getElement().setZIndex(_wraith.getElement().getZIndex() + 1);
    if (_wraith.getElement().isMirroredHor() != _gun.getElement().isMirroredHor()) { _gun.getElement().mirrorHor(); }
    _gun.update(getGunPos(), angle);
    
    return result;
}