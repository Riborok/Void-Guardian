#include "../../../../include/game/entity/enemy/Enemy.hpp"

#include "../../../../include/additionally/RandomGenerator.hpp"

Enemy::Enemy(Character&& character, Gun&& gun, const EntityInfo& entity_info, const sf::Vector2f &gun_offset):
    FightingEntity(entity_info, gun_offset, std::move(character), std::move(gun)) { }

MovementUtils::MovementMask Enemy::getMovementMask(const EnemyMovementGenerator& enemy_movement_generator) {
    if (_enemy_management.steps_amount == 0) {
        _enemy_management.movement_mask = RandomGenerator::getRandom(enemy_movement_generator.random_movement_mask);
        _enemy_management.steps_amount = RandomGenerator::getRandom(enemy_movement_generator.random_steps_amount);
    }
    --_enemy_management.steps_amount;
    return _enemy_management.movement_mask;
}

void Enemy::markCollision() { _enemy_management.steps_amount = 0; }