﻿// ReSharper disable CppClangTidyClangDiagnosticCoveredSwitchDefault CppClangTidyClangDiagnosticImplicitFallthrough CppInconsistentNaming
#include <array>
#include <stdexcept>
#include "../../../../include/game/construction/MapCreation/LocationTransformation.hpp"
#include "../../../../include/game/construction/MapCreation/PositionalMap.hpp"

MinMaxPoint LocationTransformation::getMinMaxPoint(const LocationInfos &location_infos,
                                                   const sf::Vector2i &max_size, const sf::Vector2i &block_delta) {
    sf::Vector2i min(INT_MAX, INT_MAX);
    sf::Vector2i max(INT_MIN, INT_MIN);
    for (const auto *loc_info : location_infos) {
        const auto [p0, p1](loc_info->getRangeRect(block_delta, max_size));
    
        if (p0.x < min.x)
            min.x = p0.x;
        if (p0.y < min.y)
            min.y = p0.y;
    
        if (p1.x > max.x)
            max.x = p1.x;
        if (p1.y > max.y)
            max.y = p1.y;
    }
    return std::make_pair(min, max);
}

namespace LocationTransformation::BuildLocation {
    typedef PositionalMap<Location> LocationMap;
    typedef std::vector<Location*> Locations;
    
    void createHorTransition(const RoomCreator &room_creator, const Polygon &left_polygon, Polygon const &right_polygon) {
        room_creator.createHorTransition(
            static_cast<sf::Vector2i>(left_polygon.getPoints()[1]),
            static_cast<int>(right_polygon.getPoints()[0].x)
        );
    }
    void createVertTransition(const RoomCreator &room_creator, const Polygon &top_polygon, const Polygon &bottom_polygon) {
        room_creator.createVertTransition(
            static_cast<sf::Vector2i>(top_polygon.getPoints()[3]),
            static_cast<int>(bottom_polygon.getPoints()[0].y)
        );
    }
    void createTransition(const RoomCreator &room_creator, const DoorOpening door_opening,
                          const Polygon &polygon, const Polygon &neighbor) {
        switch (door_opening) {
        case DoorOpening::LEFT:
            createHorTransition(room_creator, neighbor, polygon);   
            break;
        case DoorOpening::RIGHT:
            createHorTransition(room_creator, polygon, neighbor);      
            break;
        case DoorOpening::TOP:
            createVertTransition(room_creator, neighbor, polygon);   
            break;
        case DoorOpening::BOTTOM:
            createVertTransition(room_creator, polygon, neighbor);
            break;
        case DoorOpening::NONE:
        default:
            throw std::invalid_argument("Invalid DoorOpening type");
        }
    }
    int getDoorSizeCount(const RoomCreator &room_creator, const DoorOpening door_opening) {
        return isVert(door_opening) ? room_creator.getDoorSizeCount().y : room_creator.getDoorSizeCount().x;
    }
    size_t getDoorIndex(const DoorOpeningMask mask, const DoorOpening door_opening) {
        size_t result = 0;
        switch (door_opening) {
        case DoorOpening::BOTTOM    :   result += hasTopDoor(mask);
        case DoorOpening::TOP       :   result += hasRightDoor(mask);
        case DoorOpening::RIGHT     :   result += hasLeftDoor(mask);
        case DoorOpening::LEFT      :   return result;
        case DoorOpening::NONE      :
        default                     :   throw std::invalid_argument("Invalid DoorOpening type");
        }
    }
    size_t getMissedBlockIndex(const LocationInfo *location_info, const DoorOpening door_opening, const int count) {
        const DoorOpeningMask door_outgoing_mask = location_info->getOutgoingDoorsMask();
        const DoorOpeningMask door_incoming_mask = location_info->getIncomingDoorsMask();
        return getDoorIndex(door_outgoing_mask | door_incoming_mask, door_opening) * count;
    }
    const LocationInfo *getNeighborLocationInfo(const LocationInfo *location_info, const DoorOpening door_opening) {
        const DoorOpeningMask door_outgoing_mask = location_info->getOutgoingDoorsMask();
        const size_t door_index = getDoorIndex(door_outgoing_mask, door_opening);
        return location_info->getOutgoingDoors()[door_index];
    }
    void handleDoor(const RoomCreator &room_creator, const LocationMap &locations, const LocationInfo *location_info) {
        for (const DoorOpening door_opening : DOOR_OPENINGS) {
            if (hasDoor(location_info->getOutgoingDoorsMask(), door_opening)) {
                const auto *neighbor_location_info = getNeighborLocationInfo(location_info, door_opening);

                const int door_size_count = getDoorSizeCount(room_creator, door_opening);
                const size_t missed_index = getMissedBlockIndex(location_info, door_opening, door_size_count);
                const size_t neighbor_missed_index = getMissedBlockIndex(neighbor_location_info,
                    getOppositeDoor(door_opening), door_size_count);

                auto *location = locations.get(location_info->getPosition());
                auto *neighbor_location = locations.get(neighbor_location_info->getPosition());
                createTransition(room_creator, door_opening,
                    location->getMissedBlocks()[missed_index]->getPolygon(),
                    neighbor_location->getMissedBlocks()[neighbor_missed_index]->getPolygon());
            }
        }
    }
    void buildTransitions(const LocationInfos &location_infos, const RoomCreator &room_creator,
                          const LocationMap &locations) {
        for (const auto *loc_info : location_infos)
            handleDoor(room_creator, locations, loc_info);
    }
    void buildLocations(const LocationInfos &location_infos, const sf::Vector2i &max_size,
            RoomCreator &room_creator, LocationMap &locations) {
        for (const auto *loc_info : location_infos) { 
            const auto [p0, p1](loc_info->getRangeRect(room_creator.getBlockDelta(), max_size));
            const size_t door_opening = loc_info->getIncomingDoorsMask() | loc_info->getOutgoingDoorsMask();
            locations.set(room_creator.create(p0, p1, door_opening), loc_info->getPosition());
        }
    }
    void addToQuadtreeLocs(const Locations &locations, QuadtreeLoc &quadtree_locs) {
        for (const auto *location : locations)
            quadtree_locs.insert(location);
    }
}

void LocationTransformation::buildLocation(const LocationInfos &location_infos, const sf::Vector2i &last_index,
        const sf::Vector2i &max_size, RoomCreator &room_creator, QuadtreeLoc &quadtree_locs) {
    BuildLocation::LocationMap locations(last_index);

    BuildLocation::buildLocations(location_infos, max_size, room_creator, locations);
    BuildLocation::buildTransitions(location_infos, room_creator, locations);
    BuildLocation::addToQuadtreeLocs(locations.getItemSequence(), quadtree_locs);
}