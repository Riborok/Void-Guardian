#include "../../../include/game/entity/Entity.hpp"

Entity::Entity(const EntityInfo &info, const size_t id) : Identifiable(id), _info(info),
    _health(info.health), _armor_strength(info.armor_strength) {}

float Entity::calcHealthRatio() const {
    return static_cast<float>(_health) / static_cast<float>(_info.health);
}

float Entity::calcArmorStrengthRatio() const {
    return static_cast<float>(_armor_strength) / static_cast<float>(_info.armor_strength);
}

int Entity::getHealth() const {
    return _health;
}

float Entity::getArmorStrengthRatio() const {
    return _armor_strength;
}

bool Entity::isDead() const { return _health <= 0; }

void Entity::takeDamage(const BulletHarm &bullet_harm) {
    _armor_strength -= bullet_harm.armor_penetration;
    if (_armor_strength < 0) { _armor_strength = 0; }

    const int damage = bullet_harm.damage - static_cast<int>(_armor_strength * static_cast<float>(_info.armor));
    if (damage > 0) { _health -= damage; }
}