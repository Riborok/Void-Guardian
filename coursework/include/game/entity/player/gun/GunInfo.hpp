#pragma once

struct BulletMultipliers final {
    float damage_mult;
    float armor_penetration_mult;
    float speed_mult;
    BulletMultipliers(const float damage_mult, const float armor_penetration_mult, const float speed_mult) :
        damage_mult(damage_mult), armor_penetration_mult(armor_penetration_mult), speed_mult(speed_mult) { }
};

struct GunStats final {
    int reload_time;
    explicit GunStats(const int reload_time) : reload_time(reload_time) { }
};

struct GunInfo final {
    BulletMultipliers bullet_multipliers;
    GunStats gun_stats;
    explicit GunInfo(const int reload_time, const BulletMultipliers &bullet_multipliers):
        bullet_multipliers(bullet_multipliers), gun_stats(reload_time) { }
};
