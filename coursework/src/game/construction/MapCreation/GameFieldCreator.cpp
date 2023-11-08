#include "../../../../include/game/construction/MapCreation/GameFieldCreator.hpp"

#include "../../../../include/additionally/AdditionalFunc.hpp"
#include "../../../../include/additionally/Constants.hpp"
#include "../../../../include/game/construction/MapCreation/RoomSizeManager.hpp"

LocationInfo GameFieldCreator::createRoot() {
    std::uniform_int_distribution<int> zero_or_one{0, 1};
    
    sf::Vector2i pos;
    sf::Vector2i next_pos;
    DoorOpening neighbors_direction;

    if (AdditionalFunc::getRandom(zero_or_one) == 0) {
        if (AdditionalFunc::getRandom(zero_or_one) == 0)
        {
            pos.x = 0;
            next_pos.x = 1;
            neighbors_direction = DoorOpening::RIGHT;
        }
        else {
            pos.x = _location_map.getLastIndex().x;
            next_pos.x = _location_map.getLastIndex().x - 1;
            neighbors_direction = DoorOpening::LEFT;
        }
        std::uniform_int_distribution<int> range(0, _location_map.getLastIndex().y);
        pos.y = AdditionalFunc::getRandom(range);
        next_pos.y = pos.y;
    }
    else {
        if (AdditionalFunc::getRandom(zero_or_one) == 0) {
            pos.y = 0;
            next_pos.y = 1;
            neighbors_direction = DoorOpening::BOTTOM;
        }
        else {
            pos.y = _location_map.getLastIndex().y;
            next_pos.y = _location_map.getLastIndex().y - 1;
            neighbors_direction = DoorOpening::TOP;
        }
        std::uniform_int_distribution<int> range(0, _location_map.getLastIndex().x);
        pos.x = AdditionalFunc::getRandom(range);
        next_pos.x = pos.x;
    }
    
    LocationInfo result(pos, _loc_size.getSize(RoomType::SPAWN));
    auto* next_location = new LocationInfo(next_pos, _loc_size.getSize(RoomType::BATTLE));
    result.addOutgoingDoor(next_location, neighbors_direction);
    _location_map.set(&result);
    _location_map.set(next_location);
    return result;
}

GameFieldCreator::GameFieldCreator() noexcept : _root(createRoot()) {
}

[[nodiscard]] sf::Vector2f GameFieldCreator::getStartPoint(const sf::Vector2i &block_delta) const {
    const auto [p0, p1] = _root.getRangeRect(block_delta, _loc_size.getMaxSize());
    return {static_cast<float>((p0.x + p1.x)) / 2.0f, static_cast<float>((p0.y + p1.y)) / 2.0f};
}

GameField GameFieldCreator::create(const int block_num, const int background_num,
        const sf::Vector2i &door_size_count,
        const sf::Vector2f &block_scale,
        const sf::Vector2f &background_scale) const {
    const auto block_delta(AdditionalFunc::getScaledSize(Constants::BLOCK_SIZE, block_scale));
    GameField result(
        LocationTransformation::getMinMaxPoint(_root, _loc_size.getMaxSize(), block_delta),
        getStartPoint(block_delta)
    );

    RoomCreator room_creator(result.quadtree_el, block_num, background_num, door_size_count, block_scale, background_scale);
    LocationTransformation::buildLocation(_root, _loc_size.getMaxSize(), _location_map.getCount(),
        room_creator, result.quadtree_loc);
    
    return result;
}
