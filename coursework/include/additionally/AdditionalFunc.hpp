#pragma once
#include <random>
#include <SFML/System/Vector2.hpp>
#include "../element/Element.hpp"

namespace AdditionalFunc {
    
    /**
     * Generates a random value using the provided distribution.
     * @param distribution The distribution to use for generating random numbers.
     * @returns A random integer based on the provided distribution.
     */
    int getRandom(std::uniform_int_distribution<int> &distribution);
    /**
     * Generates a random value using the provided distribution.
     * @param distribution The distribution to use for generating random numbers.
     * @returns A random integer based on the provided distribution.
     */
    size_t getRandom(std::uniform_int_distribution<size_t> &distribution);
    
    sf::Vector2i getScaledSize(const sf::Vector2i &size, const sf::Vector2f &scale);
    sf::Vector2f getScaledSize(const sf::Vector2f &size, const sf::Vector2f &scale);

    sf::Vector2f getWidthVector(const Element &element);
}