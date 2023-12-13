﻿#pragma once

#include "EntityInfo.hpp"
#include "../identifiable/Identifiable.hpp"
#include "bullet/BulletInfo.hpp"

class Entity {
    EntityInfo _info;
    size_t _id;
protected:
    Entity(const EntityInfo &info, const Identifiable &identifiable);
public:
    void takeDamage(const BulletStats &bullet_stats);
    [[nodiscard]] bool isDead() const;
    [[nodiscard]] size_t getId() const;
    
    virtual ~Entity() noexcept = default;
    Entity(Entity&&) noexcept = delete;
    Entity& operator=(Entity&&) noexcept = delete;
    Entity(const Entity&) noexcept = delete;
    Entity& operator=(const Entity&) noexcept = delete;
};