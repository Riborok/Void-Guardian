#include "../../../../include/game/entity/enemy/Enemy.hpp"

Enemy::Enemy(Character&& character, Gun&& gun, const EntityInfo& entity_info, const sf::Vector2f &gun_offset):
    FightingEntity(entity_info, gun_offset, std::move(character), std::move(gun)) { }