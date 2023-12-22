#include "../../../../include/game/entity/enemy/Enemy.hpp"

Enemy::Enemy(Character&& character, Gun&& gun, const EntityInfo& entity_info):
    FightingEntity(entity_info, std::move(character), std::move(gun)) { }