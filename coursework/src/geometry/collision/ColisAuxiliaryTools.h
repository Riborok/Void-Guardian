﻿#pragma once
#include <SFML/System/Vector2.hpp>

struct Projection {
    float min;
    float max;
};

struct ExtendedProjection {
    float min;
    float max;
    sf::Vector2f min_point;
    sf::Vector2f max_point;
};
