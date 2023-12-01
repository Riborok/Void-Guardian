﻿#pragma once

#include <random>
#include <unordered_set>
#include <SFML/System/Vector2.hpp>

#include "../element/ElementType.hpp"

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
}

#ifndef NDEBUG
typedef std::unordered_set<ElementType, ElementTypesHash> UniqueElements;

template <typename T>
using InitList = std::initializer_list<std::pair<const ElementType, T>>;

template <typename T>
bool checkUniqueElementTypes(const InitList<T> &pairs) {
    UniqueElements unique_elements;

    for (const auto& [fst, snd] : pairs) {
        if (unique_elements.find(fst) != unique_elements.end())
            return false;
        unique_elements.insert(fst);
    }

    return true; 
}
#endif