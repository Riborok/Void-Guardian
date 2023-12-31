﻿#include "../../include/geometry/Vector2Rotation.hpp"

#include "../../include/geometry/Trigonometry.hpp"

void Vector2Rotation::rotateVector2AroundTarget(sf::Vector2f &vector, const sf::Vector2f &target_point, const float sin, const float cos) {
    const float delta_x = vector.x - target_point.x;
    const float delta_y = vector.y - target_point.y;

    vector.x = target_point.x + delta_x * cos - delta_y * sin;
    vector.y = target_point.y + delta_x * sin + delta_y * cos;
}

void Vector2Rotation::rotateVector2(sf::Vector2f &vector, const float sin, const float cos) {
    const float x = vector.x;
    const float y = vector.y;

    vector.x = x * cos - y * sin;
    vector.y = x * sin + y * cos;
}

void Vector2Rotation::rotateVector2AroundTarget(sf::Vector2f &vector, const sf::Vector2f &target_point, const float angle) {
    rotateVector2AroundTarget(vector, target_point, Trigonometry::sinRadians(angle), Trigonometry::cosRadians(angle));
}

void Vector2Rotation::rotateVector2(sf::Vector2f &vector, const float angle) {
    rotateVector2(vector, Trigonometry::sinRadians(angle), Trigonometry::cosRadians(angle));
}