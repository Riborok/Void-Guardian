#pragma once

struct BulletStats final {
    int damage; 
    float armor_penetration; 
    BulletStats(const int damage, const float armor_penetration) :
        damage(damage), armor_penetration(armor_penetration) { }
};