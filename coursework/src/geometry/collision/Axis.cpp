#include "../../../include/geometry/collision/Axis.hpp"

#include "../../../include/geometry/GeomAuxiliaryFunc.hpp"

Axis::Axis(const sf::Vector2f v1, const sf::Vector2f v2) : sf::Vector2f(v1.y - v2.y, v2.x - v1.x) {
    GeomAuxiliaryFunc::normalize(*this);
}
