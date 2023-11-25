#pragma once
#include <SFML/System/Vector2.hpp>
#include "../../additionally/AdditionalFunc.hpp"

struct BuildingData {
    int num;
    sf::Vector2i size;
    sf::Vector2f scale;
    sf::Vector2i delta;
    BuildingData(const int num, const sf::Vector2i& size,
        const sf::Vector2f& scale) :
            num(num), size(size), scale(scale),
            delta(AdditionalFunc::getScaledSize(size, scale)) { }
};

struct LocationBuildingData final : BuildingData {
    sf::Vector2i door_size_count;
    LocationBuildingData(const int num_, const sf::Vector2i& size_,
        const sf::Vector2f& scale_, const sf::Vector2i& door_size_count) :
            BuildingData(num_, size_, scale_), door_size_count(door_size_count){ }
};
