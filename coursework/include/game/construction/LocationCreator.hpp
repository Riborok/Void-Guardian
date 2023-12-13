#pragma once
#include "Location.hpp"
#include "../identifiable/LocationIdTracker.hpp"

class LocationCreator final {
    LocationIdTracker _id_tracker;
public:
    Location *create(const AlignedRectangleData& location_data, const RoomType room_type) {
        return new Location(Rectangle(location_data), _id_tracker.generate(room_type));
    }
    
    LocationCreator() noexcept = default;
    ~LocationCreator() noexcept = default;
    LocationCreator(const LocationCreator&) noexcept = delete;
    LocationCreator& operator=(const LocationCreator&) noexcept = delete;
    LocationCreator(LocationCreator&&) noexcept = delete;
    LocationCreator& operator=(LocationCreator&&) noexcept = delete;
};