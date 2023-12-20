#include "../../../../include/game/entity/player/Player.hpp"

Player::Player(Character&& character, Gun &&gun, const EntityInfo &entity_info, const Control &control) :
    FightingEntity(entity_info, character.getElement(), std::move(character), std::move(gun)), _control(control){}

const Control& Player::getControl() const { return _control; }

bool Player::canTakeNewGun() const {
    if (_last_change_elapsed_time.getElapsedTime().asMilliseconds() >= GUN_CHANGE_COOLDOWN) {
        _last_change_elapsed_time.restart();
        return true;
    }
    return false;
}