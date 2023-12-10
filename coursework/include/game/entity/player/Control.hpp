#pragma once
#include <SFML/System/Vector2.hpp>

#include "../../input/InputHandler.hpp"

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
};

/**
 * Checks if there is a movement based on the provided control settings and key inputs.
 * @param control The Control object defining the key mappings.
 * @param input_handler The InputHandler object providing the current input states.
 * @param length The length of the movement vector.
 * @param result The resulting vector storing the movement direction and length.
 * @return true if there is a valid movement, false otherwise.
 */
bool hasMovement(const Control &control, const InputHandler &input_handler, float length, sf::Vector2f &result);