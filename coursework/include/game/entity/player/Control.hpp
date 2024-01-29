#pragma once
#include "../../input/InputInfo.hpp"
#include "../services/MovementUtils.hpp"

struct Control final {
    InputInfo forward_move;
    InputInfo backward_move;
    InputInfo left_move;
    InputInfo right_move;
    InputInfo take_item;
    InputInfo fire;
    
    Control(const InputInfo forward_key, const InputInfo backward_key, const InputInfo left_key,
            const InputInfo right_key, const InputInfo take_item, const InputInfo fire_button):
        forward_move(forward_key), backward_move(backward_key), left_move(left_key),
        right_move(right_key), take_item(take_item), fire(fire_button) {}
    Control() = default;
    /**
     * Retrieves the movement mask based on the current input states and predefined key mappings.
     * @return A MovementMask representing the detected movement based on the input.
     */
    [[nodiscard]] MovementUtils::MovementMask getMovementMask() const;
};