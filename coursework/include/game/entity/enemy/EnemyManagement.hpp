#pragma once
#include <random>
#include "../services/MovementUtils.hpp"

struct EnemyManagement final {
    MovementUtils::MovementMask movement_mask;
    size_t steps_amount;
    EnemyManagement(): movement_mask(0), steps_amount(0) {}
};

struct EnemyMovementGenerator final {
    mutable std::uniform_int_distribution<MovementUtils::MovementMask> random_movement_mask;
    mutable std::uniform_int_distribution<size_t> random_steps_amount;
    EnemyMovementGenerator():
        random_movement_mask(0, MovementUtils::MAX_MOVEMENT_MASK_VALUE), random_steps_amount(42, 242) {}
};