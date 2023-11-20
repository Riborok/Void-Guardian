#include <cmath>

#include "../../include/geometry/GeomAuxiliaryFunc.hpp"

#include "../../include/geometry/Trigonometry.hpp"

sf::Vector2f GeomAuxiliaryFunc::calcMidpoint(const sf::Vector2f &point1, const sf::Vector2f &point2) {
    return {(point1.x + point2.x) / 2, (point1.y + point2.y) / 2};
}

float GeomAuxiliaryFunc::dotProduct(const sf::Vector2f &vector1, const sf::Vector2f &vector2) {
    return vector1.x * vector2.x + vector1.y * vector2.y;
}

float GeomAuxiliaryFunc::crossProduct(const sf::Vector2f &vector1, const sf::Vector2f &vector2) {
    return vector1.x * vector2.y - vector1.y * vector2.x;
}

bool GeomAuxiliaryFunc::areOrthogonal(const float angle1, const float angle2) {
    return std::abs(std::abs(angle1 - angle2) - Trigonometry::M_PI_2_) < Trigonometry::EPSILON_RADIANS;
}

float GeomAuxiliaryFunc::calcLength(const sf::Vector2f &vector) {
    return std::sqrt(vector.x * vector.x + vector.y * vector.y);
}

void GeomAuxiliaryFunc::normalize(sf::Vector2f &vector) {
    if (const float length = calcLength(vector); length > 0) {
        vector.x /= length;
        vector.y /= length;
    }
}

void GeomAuxiliaryFunc::setLength(sf::Vector2f &vector, const float new_length) {
    if (const float length = calcLength(vector); length > 0) {
        vector.x *= new_length / length;
        vector.y *= new_length / length;
    }
}

float GeomAuxiliaryFunc::calcDistance(const sf::Vector2f &point1, const sf::Vector2f &point2) {
    const float dx = point2.x - point1.x;
    const float dy = point2.y - point1.y;
    return std::sqrt(dx * dx + dy * dy);
}