#include <cmath>

#include "../../include/geometry/Trigonometry.hpp"

namespace Trigonometry {
    float sinDegrees(const float degrees) {
        return std::sin(degrees * DEGREES_TO_RADIANS);
    }

    float cosDegrees(const float degrees) {
        return std::cos(degrees * DEGREES_TO_RADIANS);
    }

    float clampAngle(float angle, const float min_range, const float max_range) {
        while (angle < min_range)
            angle += max_range - min_range;
        while (angle >= max_range)
            angle -= max_range - min_range;
    
        return angle;
    }

    bool isAngleInQuadrant2Or3(float angle) {
        angle = clampAngle(angle);
        return angle > M_PI_2_ && angle < M_3_MULT_PI_2_;
    }

    bool isAngleInQuadrant2Or3(const sf::Vector2f &vector) {
        return isAngleInQuadrant2Or3(std::atan2(vector.y, vector.x));
    }
}
