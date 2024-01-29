#pragma once
#include "../component/bullet casing/BulletHarm.hpp"
#include "../component/gun/GunStats.hpp"

struct BulletStats final {
    BulletHarm bullet_harm;
    float speed;
    BulletStats(const int damage, const float armor_penetration, const float speed) :
        bullet_harm(damage, armor_penetration), speed(speed) { }
    BulletStats operator*(const BulletMultipliers &mult) const {
        return {
            static_cast<int>(static_cast<float>(bullet_harm.damage) * mult.damage_mult),
            bullet_harm.armor_penetration * mult.armor_penetration_mult,
            speed * mult.speed_mult
        };
    }
};