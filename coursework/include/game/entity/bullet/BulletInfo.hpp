#pragma once
#include "../player/gun/GunInfo.hpp"

struct BulletStats final {
    int damage; 
    float armor_penetration; 
    BulletStats(const int damage, const float armor_penetration) :
        damage(damage), armor_penetration(armor_penetration) { }
};

struct BulletInfo final {
    BulletStats bullet_stats;
    float speed;
    BulletInfo(const int damage, const float armor_penetration, const float speed) :
        bullet_stats(damage, armor_penetration), speed(speed) { }
    
    BulletInfo operator*(const BulletMultipliers &mult) const {
        return {
            static_cast<int>(static_cast<float>(bullet_stats.damage) * mult.damage_mult),
            bullet_stats.armor_penetration * mult.armor_penetration_mult,
            speed * mult.speed_mult
        };
    }
};