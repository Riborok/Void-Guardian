// ReSharper disable CppClangTidyClangDiagnosticCoveredSwitchDefault CppClangTidyClangDiagnosticImplicitFallthrough CppInconsistentNaming
#include "../../../../include/game/construction/MapCreation/LocationTransformation.hpp"

#include <array>
#include <stdexcept>
#include <unordered_map>

namespace GetMinMaxPoint {
    void getMinMaxPointRecursive(const LocationInfo *node, const sf::Vector2i &max_size, const sf::Vector2i &block_delta,
            sf::Vector2i &min, sf::Vector2i &max) {
        const auto [p0, p1](node->getRangeRect(block_delta, max_size));
    
        if (p0.x < min.x)
            min.x = p0.x;
        if (p0.y < min.y)
            min.y = p0.y;
    
        if (p1.x > max.x)
            max.x = p1.x;
        if (p1.y > max.y)
            max.y = p1.y;
        
        for (const auto *child : node->getOutgoingDoors())
            getMinMaxPointRecursive(child, max_size, block_delta, min, max);
    }
}

MinMaxPoint LocationTransformation::getMinMaxPoint(const LocationInfo &root, const sf::Vector2i &max_size,
        const sf::Vector2i &block_delta) {
    auto [min, max](root.getRangeRect(block_delta, max_size));

    for (const auto *child : root.getOutgoingDoors())
        GetMinMaxPoint::getMinMaxPointRecursive(child, max_size, block_delta, min, max);

    return std::make_pair(min, max);
}

namespace BuildLocation {
    struct Vector2iHash final {
        size_t operator()(const sf::Vector2i &vector) const {
            static constexpr std::hash<int> HASHER;
            const size_t hashX = HASHER(vector.x);
            const size_t hashY = HASHER(vector.y);
            return hashX ^ (hashY + 0x9e3779b9u + (hashX << 6) + (hashX >> 2));
        }
    };
    typedef std::unordered_map<sf::Vector2i, Location*, Vector2iHash> LocationMap;
    
    void buildLocationsRecursive(const LocationInfo *node, const sf::Vector2i &max_size,
            RoomCreator &room_creator, LocationMap &locations) {
        const auto [p0, p1](node->getRangeRect(room_creator.getBlockDelta(), max_size));
        const size_t door_opening = node->getIncomingDoorsMask() | node->getOutgoingDoorsMask();
        locations.insert({node->getPosition(), room_creator.create(p0, p1, door_opening)});

        for (const auto *child : node->getOutgoingDoors())
            buildLocationsRecursive(child, max_size, room_creator, locations);
    }
    size_t getDoorIndex(const LocationInfo *neighbor, const DoorOpening door_opening) {
        const auto mask = neighbor->getIncomingDoorsMask() | neighbor->getOutgoingDoorsMask();

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
    size_t getMissedBlockIndex(const size_t door_index, const int count) { return door_index * count; }
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
    void handleDoor(const RoomCreator &room_creator, LocationMap &locations, const LocationInfo *location_info,
                    const DoorOpening door_opening) {
        if (hasDoor(location_info->getOutgoingDoorsMask(), door_opening)) {
            const size_t door_index = getDoorIndex(location_info, door_opening);
            
            const auto *neighbor_location_info = location_info->getOutgoingDoors()[door_index];
            const size_t neighbor_door_index = getDoorIndex(neighbor_location_info, getOppositeDoor(door_opening));
            
            auto *location = locations[location_info->getPosition()];
            auto *neighbor_location = locations[neighbor_location_info->getPosition()];

            const int count = isVert(door_opening)
                ? room_creator.getDoorSizeCount().y
                : room_creator.getDoorSizeCount().x;
            const size_t missed_index = getMissedBlockIndex(door_index, count);
            const size_t neighbor_missed_index = getMissedBlockIndex(neighbor_door_index, count);
            createTransition(room_creator, door_opening,
                location->getMissedBlocks(false)[missed_index]->getPolygon(),
                neighbor_location->getMissedBlocks(false)[neighbor_missed_index]->getPolygon());
        }
    }
    void buildTransitionsRecursive(const LocationInfo *location_info, RoomCreator &room_creator, LocationMap &locations) {
        for (const DoorOpening door_opening : DOOR_OPENINGS)
            handleDoor(room_creator, locations, location_info, door_opening);
        
        for (const auto *child : location_info->getOutgoingDoors())
            buildTransitionsRecursive(child, room_creator, locations);
    }
    void addToQuadtreeLocs(const LocationMap &locations, QuadtreeLoc &quadtree_locs) {
        for (const auto [fst, snd] : locations)
            quadtree_locs.insert(snd);
    }
}

void LocationTransformation::buildLocation(const LocationInfo &root, const sf::Vector2i &max_size, const size_t count,
        RoomCreator &room_creator, QuadtreeLoc &quadtree_locs) {
    BuildLocation::LocationMap locations; locations.reserve(count);

    buildLocationsRecursive(&root, max_size, room_creator, locations);
    buildTransitionsRecursive(&root, room_creator, locations);
    addToQuadtreeLocs(locations, quadtree_locs);
}