#pragma once

struct EntityInfo final {
    int health;
    int armor;
    float armor_strength;
    EntityInfo(const int health, const int armor, const float armor_strength) :
        health(health), armor(armor), armor_strength(armor_strength) { }
};