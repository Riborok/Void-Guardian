#pragma once

struct BulletMultipliers final {
    float damage_mult;
    float armor_penetration_mult;
    float speed_mult;
    BulletMultipliers(const float damage_mult, const float armor_penetration_mult, const float speed_mult)
        : damage_mult(damage_mult), armor_penetration_mult(armor_penetration_mult), speed_mult(speed_mult) {}
};

struct GunInfo final {
    int reload_time;
    int num;
    BulletMultipliers bullet_multipliers;
    explicit GunInfo(const int reload_time, const int num, const BulletMultipliers &bullet_multipliers):
        reload_time(reload_time), num(num), bullet_multipliers(bullet_multipliers) { }
};
