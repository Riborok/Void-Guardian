#pragma once
#include "SpawnMap.hpp"
#include "../../../Location.hpp"

class SpawnMapCreator final {
    SpawnMap *_spawn_map;
public:
    [[nodiscard]] SpawnPoints& installLocation(const Location &location) const {
        return _spawn_map->emplace(location.getId(), SpawnPoints{}).first->second;
    }
    
    SpawnMapCreator(SpawnMap &spawn_map) noexcept: _spawn_map(&spawn_map) { }
    ~SpawnMapCreator() noexcept = default;
    SpawnMapCreator(SpawnMapCreator&&) noexcept = delete;
    SpawnMapCreator& operator=(SpawnMapCreator&&) noexcept = delete;
    SpawnMapCreator(const SpawnMapCreator&) noexcept = default;
    SpawnMapCreator& operator=(const SpawnMapCreator&) noexcept = delete;
};