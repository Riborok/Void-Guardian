#include "../../include/geometry/Vector2Rotation.hpp"

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

void Vector2Rotation::rotate90Degrees(sf::Vector2f &vector) {
    const float temp = vector.x;
    vector.x = -vector.y;
    vector.y = temp;
}
    
void Vector2Rotation::rotate180Degrees(sf::Vector2f &vector) {
    vector.x = -vector.x;
    vector.y = -vector.y;
}
    
void Vector2Rotation::rotate270Degrees(sf::Vector2f &vector) {
    const float temp = vector.x;
    vector.x = vector.y;
    vector.y = -temp;
}

constexpr float SQRT_2_INV = 0.707106781186548f; // 1 / sqrt(2)

void Vector2Rotation::rotate45Degrees(sf::Vector2f &vector) {
    const float temp = (vector.x + vector.y) * SQRT_2_INV;
    vector.y = (vector.y - vector.x) * SQRT_2_INV;
    vector.x = temp;
}

void Vector2Rotation::rotate135Degrees(sf::Vector2f &vector) {
    const float temp = (vector.x - vector.y) * SQRT_2_INV;
    vector.y = (vector.y + vector.x) * SQRT_2_INV;
    vector.x = temp;
}

void Vector2Rotation::rotate225Degrees(sf::Vector2f &vector) {
    const float temp = (-vector.x - vector.y) * SQRT_2_INV;
    vector.y = (-vector.y + vector.x) * SQRT_2_INV;
    vector.x = temp;
}

void Vector2Rotation::rotate315Degrees(sf::Vector2f &vector) {
    const float temp = (-vector.x + vector.y) * SQRT_2_INV;
    vector.y = (-vector.y - vector.x) * SQRT_2_INV;
    vector.x = temp;
}