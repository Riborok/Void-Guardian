#pragma once
#include <SFML/System/Vector2.hpp>

struct PlayerInfo final {
    sf::Vector2f pos;
    float angle;
    int wraith_num;
    int gun_num;
    PlayerInfo(const sf::Vector2f& pos, const float angle, const int wraith_num, const int gun_num)
        : pos(pos), angle(angle), wraith_num(wraith_num), gun_num(gun_num) {}
};
