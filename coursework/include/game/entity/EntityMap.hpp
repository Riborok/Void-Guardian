#pragma once
#include <unordered_map>

#include "Entity.hpp"

template <typename T, typename = std::enable_if_t<std::is_base_of_v<Entity, T>>>
class EntityMap final {
    using Map = std::unordered_map<size_t, T*>;
    
    Map _map;
public:
    EntityMap() noexcept = default;

    [[nodiscard]] const Map& getMap() const { return _map; }
    
    void insert(T* t) {
        _map.insert({t->getId(), t});
    }
    void erase(const T* t) {
        _map.erase(t->getId());
        delete t;
    }
    
    ~EntityMap() noexcept {
        for (const auto& [id, t] : _map)
            delete t;
    }
    EntityMap(EntityMap&&) noexcept = default;
    EntityMap& operator=(EntityMap&&) noexcept = default;
    EntityMap(const EntityMap&) noexcept = delete;
    EntityMap& operator=(const EntityMap&) noexcept = delete;
};