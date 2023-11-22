﻿#include "../../../../include/game/construction/MapCreation/GameFieldCreator.hpp"

#include "../../../../include/additionally/AdditionalFunc.hpp"
#include "../../../../include/game/construction/MapCreation/RoomSizeManager.hpp"

RoomType GameFieldCreator::generateType() {
    const auto &item_sequence = _location_map.getItemSequence();
    return _room_type_generator.generate(item_sequence.size() > item_sequence.capacity() / 2);
}

LocationInfo* GameFieldCreator::createLocationInfo(const sf::Vector2i& next_pos, const RoomType room_type) {
    auto* next_location = new LocationInfo(next_pos, _room_size_manager.getSize(room_type), room_type);
    _location_map.set(next_location, next_location->getPosition());
    return next_location;
}

void GameFieldCreator::createTransitions(LocationInfo &location_info, const DoorOpeningMask mask) {
    LocationInfo* connected_locations[TOTAL_DIRECTIONS];
    size_t count = 0;
    for (const DoorOpening door_opening : DOOR_OPENINGS) {
        if (hasDoor(mask, door_opening)) {
            const auto new_pos(movePosition(door_opening, location_info.getPosition()));
            if (auto *neighbour = _location_map.get(new_pos); neighbour)
                location_info.addOutgoingDoor(neighbour, door_opening);
            else {
                const auto type = generateType();
                auto* next_location = createLocationInfo(new_pos, type);
                location_info.addOutgoingDoor(next_location, door_opening);
                if (type != RoomType::PORTAL)
                    connected_locations[count++] = next_location;
            }
        }
    }
    for (size_t i = 0; i < count; ++i)
        createNeighbors(connected_locations[i]);
}

size_t GameFieldCreator::checkCoordinate(DoorOpeningMask &mask, const sf::Vector2i &pos,
        const int coord, const int critical_index, const DoorOpening door_opening) const {
    if (coord == critical_index) {
        mask &= ~doorToMask(door_opening);
        return 1;
    }
    
    const auto *neighbor = _location_map.get(movePosition(door_opening, pos));
    if (!neighbor)
        return 0;
    
    if (const auto type = neighbor->getRoomType(); type == RoomType::SPAWN || type == RoomType::PORTAL)
        mask &= ~doorToMask(door_opening);
    
    return 1;
}

size_t GameFieldCreator::getTotalObstacles(DoorOpeningMask &mask, const sf::Vector2i &pos) const {
    return checkCoordinate(mask, pos, pos.x, 0, DoorOpening::LEFT)
     + checkCoordinate(mask, pos, pos.x, _location_map.getLastIndex().x, DoorOpening::RIGHT)
     + checkCoordinate(mask, pos, pos.y, 0, DoorOpening::TOP)
     + checkCoordinate(mask, pos, pos.y, _location_map.getLastIndex().y, DoorOpening::BOTTOM);
}

DoorOpeningMask GameFieldCreator::getDirections(const sf::Vector2i &pos) {
    DoorOpeningMask result = ALL_DIRECTIONS_MASK;
    
    const size_t total_obstacles = getTotalObstacles(result, pos);
    const size_t retractions_number = total_obstacles == TOTAL_DIRECTIONS
        ? TOTAL_DIRECTIONS / 2
        : TOTAL_DIRECTIONS - total_obstacles - 1;
    
    for (size_t i = retractions_number; i > 0; --i)
        result &= ~doorToMask(_direction_generator.generateDirection());
    return result;
}

void GameFieldCreator::createNeighbors(LocationInfo* location_info) {
    const DoorOpeningMask door_opening_mask = getDirections(location_info->getPosition());
    if (door_opening_mask != 0) { createTransitions(*location_info, door_opening_mask); }
}

void GameFieldCreator::initSpawnRoomPos(sf::Vector2i& pos, sf::Vector2i& next_pos,
        DoorOpening& neighbors_direction) const {
    std::uniform_int_distribution<int> zero_or_one{0, 1};
    if (AdditionalFunc::getRandom(zero_or_one) == 0) {
        if (AdditionalFunc::getRandom(zero_or_one) == 0) {
            pos.x = 0;
            next_pos.x = 1;
            neighbors_direction = DoorOpening::RIGHT;
        }
        else {
            pos.x = _location_map.getLastIndex().x;
            next_pos.x = _location_map.getLastIndex().x - 1;
            neighbors_direction = DoorOpening::LEFT;
        }
        std::uniform_int_distribution<int> range(0, _location_map.getLastIndex().y);
        pos.y = AdditionalFunc::getRandom(range);
        next_pos.y = pos.y;
    }
    else {
        if (AdditionalFunc::getRandom(zero_or_one) == 0) {
            pos.y = 0;
            next_pos.y = 1;
            neighbors_direction = DoorOpening::BOTTOM;
        }
        else {
            pos.y = _location_map.getLastIndex().y;
            next_pos.y = _location_map.getLastIndex().y - 1;
            neighbors_direction = DoorOpening::TOP;
        }
        std::uniform_int_distribution<int> range(0, _location_map.getLastIndex().x);
        pos.x = AdditionalFunc::getRandom(range);
        next_pos.x = pos.x;
    }
}

void GameFieldCreator::createRooms() {
    sf::Vector2i pos;
    sf::Vector2i next_pos;
    DoorOpening neighbors_direction;

    initSpawnRoomPos(pos, next_pos, neighbors_direction);
    
    auto* spawn = createLocationInfo(pos, RoomType::SPAWN);
    auto* next_location = createLocationInfo(next_pos, RoomType::BATTLE);
    spawn->addOutgoingDoor(next_location, neighbors_direction);
    createNeighbors(next_location);
}

GameFieldCreator::GameFieldCreator(const sf::Vector2i &last_index) noexcept :
    _location_map(last_index) {
    createRooms();
}

[[nodiscard]] sf::Vector2f GameFieldCreator::getStartPoint(const sf::Vector2i &block_delta) const {
    const auto [p0, p1] = _location_map.getItemSequence()[0]->getRangeRect(block_delta,
        _room_size_manager.getMaxSize());
    return {static_cast<float>((p0.x + p1.x)) / 2.0f, static_cast<float>((p0.y + p1.y)) / 2.0f};
}

GameField GameFieldCreator::create(const BuildingData &background_data, const LocationBuildingData &boundary_data,
        ElementCreator &element_creator, LocationCreator &location_creator) const {
    GameField result(
        LocationTransformation::getMinMaxPoint(_location_map.getItemSequence(),
            _room_size_manager.getMaxSize(), boundary_data.delta),
        getStartPoint(boundary_data.delta)
    );

    RoomCreator room_creator(result.quadtree_el, background_data, boundary_data, element_creator, location_creator);
    LocationTransformation::buildLocation(_location_map.getItemSequence(), _location_map.getLastIndex(),
        _room_size_manager.getMaxSize(), room_creator, result.quadtree_loc);
    
    return result;
}

GameFieldCreator::~GameFieldCreator() noexcept {
    for (const auto *el : _location_map.getItemSequence())
        delete el;
}