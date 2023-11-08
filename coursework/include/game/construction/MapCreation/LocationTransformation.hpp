#pragma once
#include <SFML/System/Vector2.hpp>

#include "LocationInfo.hpp"
#include "../RoomCreator.hpp"

namespace LocationTransformation {
    MinMaxPoint getMinMaxPoint(const LocationInfo &root, const sf::Vector2i &max_size, const sf::Vector2i &block_delta);
    void buildLocation(const LocationInfo &root, const sf::Vector2i &max_size, const size_t count,
        RoomCreator &room_creator, QuadtreeLoc &quadtree_locs);
}
