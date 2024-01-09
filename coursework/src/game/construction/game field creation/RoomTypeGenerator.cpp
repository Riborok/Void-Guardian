#include "../../../../include/game/construction/game field creation/RoomTypeGenerator.hpp"

#include "../../../../include/additionally/RandomGenerator.hpp"

RoomType RoomTypeGenerator::getAvailableRandomType() const {
    return RandomGenerator::getRandom(_random_type) > 60 ? RoomType::BOX : RoomType::ARENA;
}

RoomType RoomTypeGenerator::generate(const bool generate_new_portal) {
    if (_is_created_portal || !generate_new_portal) {
        return getAvailableRandomType();
    }
    else {
        _is_created_portal = true;
        return RoomType::PORTAL;
    }
}

bool RoomTypeGenerator::isCreatedPortal() const { return _is_created_portal; }