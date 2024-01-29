#pragma once

struct BulletHarm final {
    int damage; 
    float armor_penetration; 
    BulletHarm(const int damage, const float armor_penetration) :
        damage(damage), armor_penetration(armor_penetration) { }
};