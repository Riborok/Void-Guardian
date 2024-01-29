#pragma once
#include <SFML/System/Vector2.hpp>

struct BulletMultipliers final {
    float damage_mult;
    float armor_penetration_mult;
    float speed_mult;
    BulletMultipliers(const float damage_mult, const float armor_penetration_mult, const float speed_mult) :
        damage_mult(damage_mult), armor_penetration_mult(armor_penetration_mult), speed_mult(speed_mult) { }
};

struct GunProperties final {
    int reload_time;
    sf::Vector2f owner_center_offset;
    explicit GunProperties(const int reload_time, const sf::Vector2f &owner_center_offset):
        reload_time(reload_time), owner_center_offset(owner_center_offset){ }
};

struct GunStats final {
    BulletMultipliers bullet_multipliers;
    GunProperties gun_properties;
    explicit GunStats(const int reload_time, const sf::Vector2f &owner_center_offset,
            const BulletMultipliers &bullet_multipliers = {1, 1, 1}):
        bullet_multipliers(bullet_multipliers), gun_properties(reload_time, owner_center_offset) { }
};
