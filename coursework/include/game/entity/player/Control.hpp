#pragma once
#include "../../input/InputData.hpp"
#include "../services/MovementUtils.hpp"

struct Control final {
    InputData forward_move;
    InputData backward_move;
    InputData left_move;
    InputData right_move;
    InputData take_collectible;
    InputData fire;
    
    Control(const InputData forward_key, const InputData backward_key, const InputData left_key,
            const InputData right_key, const InputData take_collectible, const InputData fire_button):
        forward_move(forward_key), backward_move(backward_key), left_move(left_key),
        right_move(right_key), take_collectible(take_collectible), fire(fire_button) {}
    Control() = default;
    /**
     * Retrieves the movement mask based on the current input states and predefined key mappings.
     * @return A MovementMask representing the detected movement based on the input.
     */
    [[nodiscard]] MovementUtils::MovementMask getMovementMask() const;
};