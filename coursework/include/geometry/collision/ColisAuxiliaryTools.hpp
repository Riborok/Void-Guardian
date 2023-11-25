#pragma once
#include <SFML/System/Vector2.hpp>

struct Projection {
    float min;
    float max;
    Projection(const float min, const float max): min(min), max(max) { }
    Projection() = default;
};

struct ExtendedProjection final : Projection {
    sf::Vector2f min_point;
    sf::Vector2f max_point;
    ExtendedProjection(const float min_, const float max_,
            const sf::Vector2f &min_point, const sf::Vector2f &max_point):
        Projection(min_, max_), min_point(min_point), max_point(max_point) {}
    ExtendedProjection() = default;
};
