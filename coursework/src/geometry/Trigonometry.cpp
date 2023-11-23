#include <cmath>

#include "../../include/geometry/Trigonometry.hpp"

constexpr float DEGREES_TO_RADIANS = Trigonometry::M_PI_ / 180.0f;
constexpr float RADIANS_TO_DEGREES = 180.0f / Trigonometry::M_PI_;

float Trigonometry::degreesToRadians(const float degrees) {
    return degrees * DEGREES_TO_RADIANS;
}

float Trigonometry::radiansToDegrees(const float radians) {
    return radians * RADIANS_TO_DEGREES;
}

float Trigonometry::sinDegrees(const float degrees) {
    return std::sin(degreesToRadians(degrees));
}

float Trigonometry::cosDegrees(const float degrees) {
    return std::cos(degreesToRadians(degrees));
}

float Trigonometry::sinRadians(const float radians) {
    return std::sin(radians);
}

float Trigonometry::cosRadians(const float radians) {
    return std::cos(radians);
}

float Trigonometry::clampAngle(float angle, const float min_range, const float max_range) {
    while (angle < min_range)
        angle += max_range - min_range;
    while (angle >= max_range)
        angle -= max_range - min_range;

    return angle;
}

bool Trigonometry::isAngleInQuadrant2Or3(float angle) {
    angle = clampAngle(angle);
    return angle > M_PI_2_ && angle < M_3_MULT_PI_2_;
}

bool Trigonometry::isAngleInQuadrant2Or3(const sf::Vector2f &vector) {
    return isAngleInQuadrant2Or3(std::atan2(vector.y, vector.x));
}