#include "../../../include/game/entity/Entity.hpp"

Entity::Entity(const EntityInfo &info, const Identifiable &identifiable) : _info(info), _id(identifiable.getId()) {}

bool Entity::isDead() const { return _info.health <= 0; }

size_t Entity::getId() const { return _id; }

void Entity::takeDamage(const BulletStats &bullet_stats) {
    _info.armor_strength -= bullet_stats.armor_penetration;
    if (_info.armor_strength < 0) { _info.armor_strength = 0; }

    const int damage = bullet_stats.damage - static_cast<int>(_info.armor_strength * static_cast<float>(_info.armor));
    if (damage > 0) { _info.health -= damage; }
}