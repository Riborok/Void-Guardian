#pragma once
#include <SFML/System/Vector2.hpp>

#include "LocationInfo.hpp"
#include "LocationInfoMap.hpp"
#include "LocationMap.hpp"
#include "../RoomCreator.hpp"
#include "../../../quadtree/quadtree type defs/QuadtreeLoc.hpp"

namespace LocationTransformation {
    typedef LocationInfoMap::Sequence LocationInfos;
    MinMaxPoint getMinMaxPoint(const LocationInfos &location_infos, const sf::Vector2i &max_size,
        const sf::Vector2i &block_delta);
    void buildLocation(const LocationInfos &location_infos, LocationMap &location_map,
        const sf::Vector2i &max_size, const RoomCreator &room_creator, QuadtreeLoc &quadtree_locs);
}