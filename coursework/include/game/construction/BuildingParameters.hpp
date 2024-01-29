#pragma once
#include <SFML/System/Vector2.hpp>
#include "../../geometry/SizeUtils.hpp"

struct BackgroundParameters {
    sf::Vector2i size;
    sf::Vector2f scale;
    sf::Vector2i delta;
    BackgroundParameters(const sf::Vector2i& size,
        const sf::Vector2f& scale) : size(size), scale(scale), delta(SizeUtils::getScaledSize(size, scale)) { }
};

struct BoundaryParameters final : BackgroundParameters {
    sf::Vector2i door_size_count;
    BoundaryParameters(const sf::Vector2i& size_, const sf::Vector2f& scale_, const sf::Vector2i& door_size_count) :
        BackgroundParameters(size_, scale_), door_size_count(door_size_count){ }
};

struct BuildingParameters final {
    BackgroundParameters background_parameters;
    BoundaryParameters boundary_parameters;
    BuildingParameters(const BackgroundParameters& background_parameters, const BoundaryParameters& boundary_parameters):
        background_parameters(background_parameters), boundary_parameters(boundary_parameters) {}
};