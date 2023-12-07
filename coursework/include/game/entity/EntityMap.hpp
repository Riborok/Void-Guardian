#pragma once
#include <unordered_map>

#include "Entity.hpp"

template <typename T, typename = std::enable_if_t<std::is_base_of_v<Entity, T>>>
class EntityMap final {
    using Map = std::unordered_map<size_t, T*>;
    
    Map _map;
public:
    using Iterator = typename Map::iterator;
    using ConstIterator = typename Map::const_iterator;
    
    EntityMap() noexcept = default;

    [[nodiscard]] const Map& getMap() const { return _map; }
    
    void insert(T* t) {
        _map.emplace(t->getId(), t);
    }
    
    Iterator erase(const T* t) {
        const auto it = _map.find(t->getId());
        delete t;
        return _map.erase(it);
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