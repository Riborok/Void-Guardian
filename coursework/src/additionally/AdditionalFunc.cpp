#include "../../include/additionally/AdditionalFunc.hpp"

std::mt19937 gen(std::random_device{}());

int AdditionalFunc::getRandom(std::uniform_int_distribution<int> &distribution) {
    return distribution(gen);
}

size_t AdditionalFunc::getRandom(std::uniform_int_distribution<size_t> &distribution) {
    return distribution(gen);
}

float AdditionalFunc::getRandom(std::uniform_real_distribution<float> &distribution) {
    return distribution(gen);
}

sf::Vector2i AdditionalFunc::getScaledSize(const sf::Vector2i &size, const sf::Vector2f &scale) {
    return {
        static_cast<int>(static_cast<float>(size.x) * scale.x),
        static_cast<int>(static_cast<float>(size.y) * scale.y)
    };
}

sf::Vector2f AdditionalFunc::getScaledSize(const sf::Vector2f &size, const sf::Vector2f &scale) {
    return { size.x * std::abs(scale.x), size.y * std::abs(scale.y) };
}

sf::Vector2f AdditionalFunc::getWidthVector(const Element &element) {
    const auto& points = element.getPolygon().getPoints();
    return points[1] - points[0];
}