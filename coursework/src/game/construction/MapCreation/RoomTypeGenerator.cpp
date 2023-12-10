#include "../../../../include/game/construction/MapCreation/RoomTypeGenerator.hpp"

#include "../../../../include/additionally/AdditionalFunc.hpp"

RoomType RoomTypeGenerator::getAvailableRandomType() const {
    return AdditionalFunc::getRandom(_random_type) > 75 ? RoomType::BOX : RoomType::BATTLE;
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