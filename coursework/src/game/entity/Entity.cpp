#include "../../../include/game/entity/Entity.hpp"

Entity::Entity(const EntityInfo &info, const Identifiable &identifiable) : Identifiable(identifiable), _info(info) {}

bool Entity::isDead() const { return _info.health <= 0; }

void Entity::takeDamage(const BulletStats &bullet_stats) {
    _info.armor_strength -= bullet_stats.armor_penetration;
    if (_info.armor_strength < 0) { _info.armor_strength = 0; }

    const int damage = bullet_stats.damage - static_cast<int>(_info.armor_strength * static_cast<float>(_info.armor));
    if (damage > 0) { _info.health -= damage; }
}