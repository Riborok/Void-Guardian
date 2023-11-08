#include "../../../../include/game/construction/MapCreation/LocationInfoMap.hpp"

#include "../../../../include/additionally/AdditionalFunc.hpp"

sf::Vector2i getLastIndex() {
    std::uniform_int_distribution<int> map_cells_size(2, 4);
    return {AdditionalFunc::getRandom(map_cells_size), AdditionalFunc::getRandom(map_cells_size)};
}

LocationInfoMap::LocationInfoMap() noexcept :
        _last_index{getLastIndex()},
        _location_info(new LocationInfo*[getTotalCount()]) {
    std::fill_n(_location_info, getTotalCount(), nullptr);
}

bool LocationInfoMap::set(LocationInfo* location_info) {
    if (const auto index = getIndex(location_info->getPosition()); !_location_info[index]) {
        _location_info[index] = location_info;
        ++_count;
        return true;
    }
    return false;
}

LocationInfo* LocationInfoMap::get(const sf::Vector2i &position) const { return _location_info[getIndex(position)]; }

const sf::Vector2i &LocationInfoMap::getLastIndex() const { return _last_index; }

LocationInfoMap::~LocationInfoMap() noexcept { delete[] _location_info; }

size_t LocationInfoMap::getIndex(const sf::Vector2i &position) const { return position.x * (_last_index.x + 1) + position.y; }

size_t LocationInfoMap::getTotalCount() const { return static_cast<size_t>((_last_index.x + 1)) * (_last_index.y + 1); }

size_t LocationInfoMap::getCount() const { return _count; }