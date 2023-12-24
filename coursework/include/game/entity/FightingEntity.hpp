#pragma once

#include "Entity.hpp"
#include "EntityInfo.hpp"
#include "component/character/Character.hpp"
#include "component/gun/Gun.hpp"

class FightingEntity : public Entity {
    static constexpr int LIMIT_TO_REGENERATION = 7420;
    static constexpr int INTERVAL_OF_REGENERATION = 1000;
    static constexpr int REGENERATION_FACTOR = 20;
    
    sf::Vector2f _gun_offset;
    Character _character;
    Gun _gun;
    int _time_without_damage = 0;
    bool _has_regeneration = false;

    void applyRegeneration();
    void checkRegenerationActivation();
protected:
    FightingEntity(const EntityInfo &info, const sf::Vector2f &gun_offset, Character&& character, Gun &&gun);
public:
    [[nodiscard]] sf::Vector2f getGunPos() const;
    [[nodiscard]] const Character &getCharacter() const;
    [[nodiscard]] const Gun &getGun() const;
    void updateTimeWithoutDamage(const int delta_time);
    void takeDamage(const BulletStats &bullet_stats) override;
    
    void checkMirror(const bool is_angle_in_quadrant2_or3) const;
    Gun takeNewGun(Gun&& gun);
    
    ~FightingEntity() noexcept override = default;
    FightingEntity(FightingEntity&&) noexcept = delete;
    FightingEntity& operator=(FightingEntity&&) noexcept = delete;
    FightingEntity(const FightingEntity&) noexcept = delete;
    FightingEntity& operator=(const FightingEntity&) noexcept = delete;
};