#pragma once
#include <SFML/System/Vector2.hpp>

struct LaunchData {
    sf::Vector2f point;
    sf::Vector2f velocity;
    float angle;
    int num;
    LaunchData(const sf::Vector2f &point, const sf::Vector2f &velocity, const float angle, const int num):
        point(point), velocity(velocity), angle(angle), num(num) {}
    LaunchData() = default;
};