#include "../../../../include/game/construction/game field creation/RoomSizeManager.hpp"

#include "../../../../include/additionally/LevelParameters.hpp"
#include "../../../../include/additionally/RandomGenerator.hpp"

RoomSizeManager::RoomSizeManager(const size_t lvl) :
    _arena_random_size(LevelParameters::getArenaRandomSize(lvl)),
    _max_size(_arena_random_size.random_size_x.max() + MAX_SIZE_OFFSET,
        _arena_random_size.random_size_y.max() + MAX_SIZE_OFFSET){}

int RoomSizeManager::makeEven(const int value) { return value & ~1; }

sf::Vector2i RoomSizeManager::getSize(const RoomType type) const {
    switch (type) {
    case RoomType::SPAWN:
    case RoomType::PORTAL:
        return {12, 10};
    case RoomType::BOX:
        return {8, 8};
    case RoomType::ARENA:
        return {makeEven(RandomGenerator::getRandom(_arena_random_size.random_size_x)),
            makeEven(RandomGenerator::getRandom(_arena_random_size.random_size_y))};
    default: 
        throw std::invalid_argument("Invalid RoomType");
    }
}

const sf::Vector2i &RoomSizeManager::getMaxSize() const { return _max_size; }