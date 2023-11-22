#include "../../include/additionally/AdditionalFunc.hpp"

namespace InnerLogic {
    std::mt19937 gen(std::random_device{}());
}

int AdditionalFunc::getRandom(std::uniform_int_distribution<int> &distribution) {
    return distribution(InnerLogic::gen);
}
size_t AdditionalFunc::getRandom(std::uniform_int_distribution<size_t> &distribution) {
    return distribution(InnerLogic::gen);
}

sf::Vector2i AdditionalFunc::getScaledSize(const sf::Vector2i &size, const sf::Vector2f &scale) {
    return {
        static_cast<int>(static_cast<float>(size.x) * scale.x),
        static_cast<int>(static_cast<float>(size.y) * scale.y)
    };
}

sf::Vector2f AdditionalFunc::getScaledSize(const sf::Vector2f &size, const sf::Vector2f &scale) {
    return { size.x * scale.x, size.y * scale.y };
}