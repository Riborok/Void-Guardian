#pragma once
#include <utility>
#include <SFML/System/Vector2.hpp>

#include "../RoomType.hpp"
#include "../DoorOpening.hpp"

class LocationInfo final {
    typedef std::pair<const sf::Vector2i, const sf::Vector2i> RangeRect;

    RoomType _room_type;
    sf::Vector2i _position;
    sf::Vector2i _size;
    DoorOpeningMask _incoming_doors_mask;
    DoorOpeningMask _outgoing_doors_mask;
    LocationInfo* _outgoing_doors[TOTAL_DIRECTIONS];
    
    void addIncomingDoor(const DoorOpening door_opening);
public:
    LocationInfo(const sf::Vector2i& pos, const sf::Vector2i& sz, const RoomType room_type);

    [[nodiscard]] RangeRect getRangeRect(const sf::Vector2i &block_delta, const sf::Vector2i &max_size) const;
    
    void addOutgoingDoor(LocationInfo* location_info, const DoorOpening door_opening);

    [[nodiscard]] const sf::Vector2i &getPosition() const;
    [[nodiscard]] RoomType getRoomType() const;
    [[nodiscard]] DoorOpeningMask getIncomingDoorsMask() const;
    [[nodiscard]] DoorOpeningMask getOutgoingDoorsMask() const;
    [[nodiscard]] const LocationInfo* getOutgoingDoor(const DoorOpening door_opening) const;
    
    ~LocationInfo() noexcept = default;
    LocationInfo(LocationInfo&&) noexcept = default;
    LocationInfo& operator=(LocationInfo&&) noexcept = delete;
    LocationInfo(const LocationInfo&) noexcept = delete;
    LocationInfo& operator=(const LocationInfo&) noexcept = delete;
};
