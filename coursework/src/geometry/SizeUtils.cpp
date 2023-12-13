#include "../../include/geometry/SizeUtils.hpp"

sf::Vector2i SizeUtils::getScaledSize(const sf::Vector2i &size, const sf::Vector2f &scale) {
    return {
        static_cast<int>(static_cast<float>(size.x) * scale.x),
        static_cast<int>(static_cast<float>(size.y) * scale.y)
    };
}

sf::Vector2f SizeUtils::getScaledSize(const sf::Vector2f &size, const sf::Vector2f &scale) {
    return { size.x * std::abs(scale.x), size.y * std::abs(scale.y) };
}

sf::Vector2f SizeUtils::getWidthVector(const Element &element) {
    const auto& points = element.getPolygon().getPoints();
    return points[1] - points[0];
}