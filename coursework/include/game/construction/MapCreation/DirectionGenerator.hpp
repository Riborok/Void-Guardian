#pragma once
#include <random>

#include "../DoorOpening.hpp"
#include "../../../additionally/RandomGenerator.hpp"

class DirectionGenerator final {
    mutable std::uniform_int_distribution<size_t> _direction_index{0, TOTAL_DIRECTIONS - 1};
public:
    DoorOpening generateDirection() const { return DOOR_OPENINGS[RandomGenerator::getRandom(_direction_index)]; }

    DirectionGenerator() noexcept = default;
    ~DirectionGenerator() noexcept = default;
    DirectionGenerator(DirectionGenerator&&) noexcept = delete;
    DirectionGenerator& operator=(DirectionGenerator&&) noexcept = delete;
    DirectionGenerator(const DirectionGenerator&) noexcept = delete;
    DirectionGenerator& operator=(const DirectionGenerator&) noexcept = delete;
};