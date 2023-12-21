#pragma once

#include "Entity.hpp"
#include "EntityInfo.hpp"
#include "component/character/Character.hpp"
#include "component/gun/Gun.hpp"

class FightingEntity : public Entity {
    Character _character;
    Gun _gun;
protected:
    FightingEntity(const EntityInfo &info, Character&& character, Gun &&gun);
public:
    [[nodiscard]] sf::Vector2f getGunPos() const;
    [[nodiscard]] const Character &getCharacter() const;
    [[nodiscard]] const Gun &getGun() const;
    
    void checkMirror(const bool is_angle_in_quadrant2_or3) const;
    Gun takeNewGun(Gun&& gun);
    
    ~FightingEntity() noexcept override = default;
    FightingEntity(FightingEntity&&) noexcept = delete;
    FightingEntity& operator=(FightingEntity&&) noexcept = delete;
    FightingEntity(const FightingEntity&) noexcept = delete;
    FightingEntity& operator=(const FightingEntity&) noexcept = delete;
};