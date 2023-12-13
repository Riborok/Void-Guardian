#pragma once
#include <SFML/System/Vector2.hpp>
#include "../../geometry/SizeUtils.hpp"

struct BackgroundData {
    int num;
    sf::Vector2i size;
    sf::Vector2f scale;
    sf::Vector2i delta;
    BackgroundData(const int num, const sf::Vector2i& size,
        const sf::Vector2f& scale) :
            num(num), size(size), scale(scale),
            delta(SizeUtils::getScaledSize(size, scale)) { }
};

struct BoundaryData final : BackgroundData {
    sf::Vector2i door_size_count;
    BoundaryData(const int num_, const sf::Vector2i& size_,
        const sf::Vector2f& scale_, const sf::Vector2i& door_size_count) :
            BackgroundData(num_, size_, scale_), door_size_count(door_size_count){ }
};

struct BuildingData final {
    BackgroundData background_data;
    BoundaryData boundary_data;
    BuildingData(const BackgroundData& background, const BoundaryData& boundary):
        background_data(background), boundary_data(boundary) {}
};