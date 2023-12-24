﻿#include "../../../include/game/entity/Entity.hpp"

Entity::Entity(const EntityInfo &info, const size_t id) : Identifiable(id), _info(info),
    _health(info.health), _armor_strength(info.armor_strength) {}

bool Entity::isDead() const { return _health <= 0; }

void Entity::takeDamage(const BulletStats &bullet_stats) {
    _armor_strength -= bullet_stats.armor_penetration;
    if (_info.armor_strength < 0) { _armor_strength = 0; }

    const int damage = bullet_stats.damage - static_cast<int>(_info.armor_strength * static_cast<float>(_info.armor));
    if (damage > 0) { _health -= damage; }
}