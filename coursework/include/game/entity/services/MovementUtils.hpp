#pragma once
#include <SFML/System/Vector2.hpp>

namespace MovementUtils {
    typedef size_t MovementMask;
    enum : MovementMask {
        NONE = 0,
        FORWARD = 1 << 0,
        BACKWARD = 1 << 1,
        LEFT = 1 << 2,
        RIGHT = 1 << 3
    };
    static constexpr MovementMask MAX_MOVEMENT_MASK_VALUE = RIGHT;
    /**
     * Checks if there is a movement based on the provided movement mask, length, and calculates the resulting vector.
     * @param movement_mask The MovementMask obtained from key inputs.
     * @param length The length of the movement vector.
     * @param result The resulting vector storing the movement direction and length.
     * @return true if there is a valid movement, false otherwise.
     */
    bool hasMovement(const MovementMask movement_mask, float length, sf::Vector2f &result);
}