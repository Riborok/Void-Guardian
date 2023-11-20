#pragma once
#include <random>

#include "../DoorOpening.hpp"
#include "../../../additionally/AdditionalFunc.hpp"

class DirectionGenerator final {
    std::uniform_int_distribution<size_t> _direction_index{0, TOTAL_DIRECTIONS - 1};
public:
    DoorOpening generateDirection() { return DOOR_OPENINGS[AdditionalFunc::getRandom(_direction_index)]; }

    DirectionGenerator() noexcept = default;
    ~DirectionGenerator() noexcept = default;
    DirectionGenerator(DirectionGenerator&&) noexcept = delete;
    DirectionGenerator& operator=(DirectionGenerator&&) noexcept = delete;
    DirectionGenerator(const DirectionGenerator&) noexcept = delete;
    DirectionGenerator& operator=(const DirectionGenerator&) noexcept = delete;
};