﻿#include <cmath>
#include "../../include/geometry/GeomAuxiliaryFunc.hpp"
#include "../../include/geometry/Trigonometry.hpp"

float GeomAuxiliaryFunc::calcBoundingRectDiameter(const Polygon& polygon) {
    return std::hypot(polygon.getBoundingRectWidth(), polygon.getBoundingRectHeight());
}

float GeomAuxiliaryFunc::calcCoDirectionalScaleFactor(const sf::Vector2f &vector1, const sf::Vector2f &vector2) {
    return vector1.x / vector2.x;
}

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
    const float delta_angle = std::abs(angle1 - angle2);
    return std::abs(delta_angle - Trigonometry::M_PI_2_) < Trigonometry::EPSILON_RADIANS ||
           std::abs(delta_angle - Trigonometry::M_3_MULT_PI_2_) < Trigonometry::EPSILON_RADIANS;
}

bool GeomAuxiliaryFunc::areCollinear(const float angle1, const float angle2) {
    const float diff = std::abs(angle1 - angle2);
    return diff < Trigonometry::EPSILON_RADIANS || 
           std::abs(diff - Trigonometry::M_PI_) < Trigonometry::EPSILON_RADIANS || 
           std::abs(diff - Trigonometry::M_2_MULT_PI_) < Trigonometry::EPSILON_RADIANS;
}

bool GeomAuxiliaryFunc::areOrthogonalOrCollinear(const float angle1, const float angle2) {
    return areOrthogonal(angle1, angle2) || areCollinear(angle1, angle2);
}

float GeomAuxiliaryFunc::calcLength(const sf::Vector2f &vector) {
    return std::hypot(vector.x, vector.y);
}

void GeomAuxiliaryFunc::normalize(sf::Vector2f &vector) {
    if (const float length = calcLength(vector); length > 0) {
        vector.x /= length;
        vector.y /= length;
    }
}

float GeomAuxiliaryFunc::calcAngle(const sf::Vector2f &vector) {
    return std::atan2(vector.y, vector.x);
}

void GeomAuxiliaryFunc::setLength(sf::Vector2f &vector, const float new_length) {
    if (const float length = calcLength(vector); length > 0) {
        vector.x *= new_length / length;
        vector.y *= new_length / length;
    }
}

float GeomAuxiliaryFunc::calcDistance(const sf::Vector2f &point1, const sf::Vector2f &point2) {
    return std::hypot(point2.x - point1.x, point2.y - point1.y);
}

sf::Vector2i GeomAuxiliaryFunc::multiplyVectors(const sf::Vector2i& vector1, const sf::Vector2i& vector2) {
    return {vector1.x * vector2.x, vector1.y * vector2.y};
}