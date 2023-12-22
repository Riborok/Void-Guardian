#pragma once
#include "../FightingEntity.hpp"

class Enemy final : public FightingEntity {
public:
    Enemy(Character&& character, Gun &&gun, const EntityInfo &entity_info, const sf::Vector2f &gun_offset);
    
    ~Enemy() noexcept override = default;
    Enemy(const Enemy&) noexcept = delete;
    Enemy& operator=(const Enemy&) noexcept = delete;
    Enemy(Enemy&&) noexcept = delete;
    Enemy& operator=(Enemy&&) noexcept = delete;
};