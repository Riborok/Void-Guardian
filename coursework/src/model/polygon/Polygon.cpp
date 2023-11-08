#include <SFML/System/Vector2.hpp>

#include "../../../include/model/polygon/Polygon.hpp"

#include "../../../include/geometry/Trigonometry.hpp"
#include "../../../include/geometry/Vector2Rotation.hpp"

const std::vector<sf::Vector2f> &Polygon::getPoints() const { return _points; }

void Polygon::move(const sf::Vector2f &vector) {
    for (auto &point : _points)
        point += vector;
}

void Polygon::rotate(const sf::Vector2f &target, const float delta_angle) {
    const float sin = Trigonometry::sinDegrees(delta_angle);
    const float cos = Trigonometry::cosDegrees(delta_angle);
    
    for (auto &point : _points)
        Vector2Rotation::rotateVector2AroundTarget(point, target, sin, cos); 
}

Polygon::Polygon(std::vector<sf::Vector2f> &&points): _points(std::move(points)) { }