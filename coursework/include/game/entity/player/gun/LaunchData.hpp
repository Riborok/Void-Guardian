#pragma once
#include <SFML/System/Vector2.hpp>

struct LaunchData {
    sf::Vector2f point;
    float angle;
    int num;
    LaunchData(const sf::Vector2f &point, const float angle, const int num):
        point(point), angle(angle), num(num) {}
    LaunchData() = default;
};