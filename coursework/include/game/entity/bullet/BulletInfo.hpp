#pragma once
#include "../player/gun/GunInfo.hpp"

struct BulletStats {
    int damage; 
    float armor_penetration; 
    BulletStats(const int damage, const float armor_penetration) :
        damage(damage), armor_penetration(armor_penetration) { }
};

struct BulletInfo final : BulletStats {
    float speed;   
    BulletInfo(const int damage_, const float armor_penetration_, const float speed) :
        BulletStats(damage_, armor_penetration_), speed(speed) { }
    void multiply(const BulletMultipliers &mult) {
        damage = static_cast<int>(static_cast<float>(damage) * mult.damage_mult);
        armor_penetration *= mult.armor_penetration_mult;
        speed *= mult.speed_mult;
    }
};