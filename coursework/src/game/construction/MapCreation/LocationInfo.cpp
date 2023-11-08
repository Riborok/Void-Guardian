﻿#include "../../../../include/game/construction/MapCreation/LocationInfo.hpp"

#include "../../../../include/game/construction/MapCreation/RoomSizeManager.hpp"

LocationInfo::LocationInfo(const sf::Vector2i& pos, const sf::Vector2i& sz):
        _position(pos), _size(sz),
        _incoming_doors_mask(static_cast<DoorOpeningMask>(DoorOpening::NONE)),
        _outgoing_doors_mask(static_cast<DoorOpeningMask>(DoorOpening::NONE)) {
    _outgoing_doors.reserve(AMOUNT_OF_DIRECTIONS);
}

LocationInfo::~LocationInfo() noexcept {
    for (const auto* child : _outgoing_doors)
        delete child;
}

LocationInfo::RangeRect LocationInfo::getRangeRect(const sf::Vector2i &block_delta, const sf::Vector2i &max_size) const {
    const sf::Vector2i global_offset(max_size.x * _position.x, max_size.y * _position.y);
    const sf::Vector2i local_offset((max_size.x - _size.x) / 2, (max_size.y - _size.y) / 2);

    const sf::Vector2i start_point((global_offset.x + local_offset.x) * block_delta.x,
        (global_offset.y + local_offset.y) * block_delta.x);
    const sf::Vector2i end_point(start_point.x + _size.x * block_delta.x,
        start_point.y + _size.y * block_delta.y);
        
    return std::make_pair(start_point, end_point);
}

const sf::Vector2i &LocationInfo::getPosition() const { return _position; }

DoorOpeningMask LocationInfo::getIncomingDoorsMask() const { return _incoming_doors_mask; } 

DoorOpeningMask LocationInfo::getOutgoingDoorsMask() const { return _outgoing_doors_mask; }

const LocationInfo::OutgoingDoors &LocationInfo::getOutgoingDoors() const { return _outgoing_doors; }

void LocationInfo::addIncomingDoor(const DoorOpening door_opening) {
    _incoming_doors_mask |= static_cast<DoorOpeningMask>(door_opening);
}

void LocationInfo::addOutgoingDoor(LocationInfo* location_info, const DoorOpening door_opening) {
    if (const auto bit = static_cast<DoorOpeningMask>(door_opening); !((_incoming_doors_mask | _outgoing_doors_mask) & bit)) {
        location_info->addIncomingDoor(getOppositeDoor(door_opening));
        _outgoing_doors_mask |= bit;
        _outgoing_doors.push_back(location_info);
    }
}
