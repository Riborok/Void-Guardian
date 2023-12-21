#pragma once
#include <SFML/System/Vector2.hpp>

struct FightingEntityInfo final {
    sf::Vector2f pos;
    float angle;
    size_t character_num;
    size_t gun_num;
    FightingEntityInfo(const sf::Vector2f& pos, const float angle, const size_t character_num, const size_t gun_num):
        pos(pos), angle(angle), character_num(character_num), gun_num(gun_num) {}
};