#pragma once

#include "EntityInfo.hpp"
#include "../identifiable/Identifiable.hpp"
#include "bullet/BulletInfo.hpp"

class Entity : public Identifiable {
    EntityInfo _info;
protected:
    Entity(const EntityInfo &info, const size_t id);
public:
    void takeDamage(const BulletStats &bullet_stats);
    [[nodiscard]] bool isDead() const;
    
    ~Entity() noexcept override = default;
    Entity(Entity&&) noexcept = delete;
    Entity& operator=(Entity&&) noexcept = delete;
    Entity(const Entity&) noexcept = delete;
    Entity& operator=(const Entity&) noexcept = delete;
};