#include "../../../include/game/entity/FightingEntity.hpp"

FightingEntity::FightingEntity(const EntityInfo &info, const sf::Vector2f &gun_offset, Character&& character, Gun &&gun):
        Entity(info, character.getElement().getId()), _gun_offset(gun_offset),
        _character(std::move(character)), _gun(std::move(gun)) {
    _gun.getElement().setZIndex(_character.getElement().getZIndex() + 1);
}

sf::Vector2f FightingEntity::getGunPos() const {
    auto result(_character.getElement().getPolygon().calcCenter());
    const auto& center_offset = _gun.getCenterOffset();
    const float offset_x = center_offset.x + _gun_offset.x;
    const float offset_y = center_offset.y + _gun_offset.y;
    result.x += _gun.getElement().isMirroredHor() ? -offset_x : offset_x;
    result.y += offset_y;
    return result;
}

const Character &FightingEntity::getCharacter() const { return _character; }
const Gun &FightingEntity::getGun() const { return _gun; }

void FightingEntity::checkMirror(const bool is_angle_in_quadrant2_or3) const {
    const bool is_mirrored = _character.getElement().isMirroredHor();
    if ((is_mirrored && !is_angle_in_quadrant2_or3) || (!is_mirrored && is_angle_in_quadrant2_or3)) {
        _character.getElement().mirrorHor();
        _gun.getElement().mirrorHor();
    }
}

Gun FightingEntity::takeNewGun(Gun&& gun) {
    const float angle = _gun.getElement().getPolygon().getRotation();
    Gun result = std::move(_gun);
    
    _gun = std::move(gun);
    _gun.getElement().setZIndex(_character.getElement().getZIndex() + 1);
    if (_character.getElement().isMirroredHor() != _gun.getElement().isMirroredHor()) { _gun.getElement().mirrorHor(); }
    _gun.update(getGunPos(), angle);
    
    return result;
}