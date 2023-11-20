#pragma once
#include <SFML/System/Vector2.hpp>

#include "LocationInfo.hpp"
#include "../RoomCreator.hpp"
#include "../../../additionally/QuadtreeLoc.hpp"

namespace LocationTransformation {
    typedef std::vector<LocationInfo*> LocationInfos;
    MinMaxPoint getMinMaxPoint(const LocationInfos &location_infos, const sf::Vector2i &max_size,
        const sf::Vector2i &block_delta);
    void buildLocation(const LocationInfos &location_infos, const sf::Vector2i &last_index,
        const sf::Vector2i &max_size, RoomCreator &room_creator, QuadtreeLoc &quadtree_locs);
}