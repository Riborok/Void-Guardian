#pragma once

#include "EntityInfo.hpp"
#include "../identifiable/Identifiable.hpp"
#include "bullet/BulletStats.hpp"

class Entity : public Identifiable {
protected:
    const EntityInfo _info;
    int _health;
    float _armor_strength;
    Entity(const EntityInfo &info, const size_t id);
public:
    [[nodiscard]] float calcHealthRatio() const;
    [[nodiscard]] float calcArmorStrengthRatio() const;
    [[nodiscard]] int getHealth() const;
    [[nodiscard]] float getArmorStrengthRatio() const;
    virtual void takeDamage(const BulletHarm &bullet_harm);
    [[nodiscard]] bool isDead() const;
    
    ~Entity() noexcept override = default;
    Entity(Entity&&) noexcept = delete;
    Entity& operator=(Entity&&) noexcept = delete;
    Entity(const Entity&) noexcept = delete;
    Entity& operator=(const Entity&) noexcept = delete;
};