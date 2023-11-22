#pragma once

#include <stdexcept>

class LocationIdTracker final {
    static constexpr size_t MAX_VALUE = SIZE_MAX;
    
    size_t _id = 0;
public:
    size_t generate() {
        return _id == MAX_VALUE
            ? throw std::runtime_error("Maximum ID is reached.")
            : _id++;
    }
    
    LocationIdTracker() noexcept = default;
    ~LocationIdTracker() noexcept = default;
    
    LocationIdTracker(const LocationIdTracker&) noexcept = delete;
    LocationIdTracker& operator=(const LocationIdTracker&) noexcept = delete;
    LocationIdTracker(LocationIdTracker&&) noexcept = delete;
    LocationIdTracker& operator=(LocationIdTracker&&) noexcept = delete;
};