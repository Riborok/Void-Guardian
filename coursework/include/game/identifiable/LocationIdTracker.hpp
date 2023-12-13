#pragma once

#include <stdint.h>
#include "../construction/RoomType.hpp"

class LocationIdTracker final {
    static constexpr size_t TYPE_DIGITS_DIVIDER = 1000;
    static constexpr size_t MAX_VALUE = SIZE_MAX / TYPE_DIGITS_DIVIDER - 1;
    
    size_t _ids[ROOM_TYPES_COUNT] = {};
public:
    static RoomType extractType(const size_t id);
    
    size_t generate(const RoomType type);
    size_t generate(const size_t type) noexcept(false);
    
    LocationIdTracker() noexcept = default;
    ~LocationIdTracker() noexcept = default;
    
    LocationIdTracker(const LocationIdTracker&) noexcept = delete;
    LocationIdTracker& operator=(const LocationIdTracker&) noexcept = delete;
    LocationIdTracker(LocationIdTracker&&) noexcept = delete;
    LocationIdTracker& operator=(LocationIdTracker&&) noexcept = delete;
};
