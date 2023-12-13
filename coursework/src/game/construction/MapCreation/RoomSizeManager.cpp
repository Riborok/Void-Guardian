﻿#include "../../../../include/game/construction/MapCreation/RoomSizeManager.hpp"
#include "../../../../include/additionally/RandomGenerator.hpp"

RoomSizeManager::RoomSizeManager(const sf::Vector2i &max_size) : _max_size(max_size) {}

int RoomSizeManager::makeEven(const int value) { return value & ~1; }

sf::Vector2i RoomSizeManager::getSize(const RoomType type) const {
    switch (type) {
    case RoomType::SPAWN:
    case RoomType::PORTAL:
        return {12, 10};
    case RoomType::BOX:
        return {8, 8};
    case RoomType::BATTLE:
        return {makeEven(RandomGenerator::getRandom(_random_size_x)),
            makeEven(RandomGenerator::getRandom(_random_size_y))};
    default:  // NOLINT(clang-diagnostic-covered-switch-default)
        throw std::invalid_argument("Invalid RoomType");
    }
}

const sf::Vector2i &RoomSizeManager::getMaxSize() const { return _max_size; }