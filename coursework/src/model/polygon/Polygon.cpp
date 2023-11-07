#include <SFML/System/Vector2.hpp>

#include "../../../include/model/polygon/Polygon.hpp"

std::vector<sf::Vector2f> &Polygon::points() { return _points; }

Polygon::Polygon(std::vector<sf::Vector2f> &&points): _points(std::move(points)) { }