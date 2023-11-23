#pragma once
#include <SFML/System/Vector2.hpp>

struct PlayerInfo final {
    sf::Vector2f scale;
    float speed;
    PlayerInfo(const sf::Vector2f &scale, const float speed): scale(scale), speed(speed){}
};
