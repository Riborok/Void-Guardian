#pragma once
#include <SFML/System/Vector2.hpp>

struct LaunchData final {
    BulletMultipliers bullet_multipliers;
    sf::Vector2f point;
    sf::Vector2f velocity;
    float angle;
    size_t num;
    LaunchData(const BulletMultipliers &bullet_multipliers, const sf::Vector2f &point,
            const sf::Vector2f &velocity, const float angle, const size_t num):
        bullet_multipliers(bullet_multipliers), point(point), velocity(velocity), angle(angle), num(num) {}
};