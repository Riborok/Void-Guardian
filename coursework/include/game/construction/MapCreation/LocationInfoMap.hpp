#pragma once
#include <SFML/System/Vector2.hpp>

#include "LocationInfo.hpp"

class LocationInfoMap final {
    sf::Vector2i _last_index;
    size_t _count = 0;
    LocationInfo* *_location_info;

    [[nodiscard]] size_t getIndex(const sf::Vector2i &position) const;
public:
    bool set(LocationInfo* location_info);
    [[nodiscard]] LocationInfo* get(const sf::Vector2i &position) const;

    [[nodiscard]] size_t getTotalCount() const;
    [[nodiscard]] size_t getCount() const;
    [[nodiscard]] const sf::Vector2i &getLastIndex() const;
    
    LocationInfoMap() noexcept;
    ~LocationInfoMap() noexcept;
    
    LocationInfoMap(LocationInfoMap&&) noexcept = delete;
    LocationInfoMap& operator=(LocationInfoMap&&) noexcept = delete;
    LocationInfoMap(const LocationInfoMap&) noexcept = delete;
    LocationInfoMap& operator=(const LocationInfoMap&) noexcept = delete;
};
