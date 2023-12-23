#pragma once
#include "EnemyManagement.hpp"
#include "../FightingEntity.hpp"

class Enemy final : public FightingEntity {
    // TODO: Make normal bot movement logic
    EnemyManagement _enemy_management;
public:
    Enemy(Character&& character, Gun &&gun, const EntityInfo &entity_info, const sf::Vector2f &gun_offset);

    // TODO: Make normal bot movement logic
    MovementUtils::MovementMask getMovementMask(const EnemyMovementGenerator &enemy_movement_generator);
    // TODO: Make normal bot movement logic
    void markCollision();
    
    ~Enemy() noexcept override = default;
    Enemy(const Enemy&) noexcept = delete;
    Enemy& operator=(const Enemy&) noexcept = delete;
    Enemy(Enemy&&) noexcept = delete;
    Enemy& operator=(Enemy&&) noexcept = delete;
};