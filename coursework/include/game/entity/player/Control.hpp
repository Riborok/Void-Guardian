#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "../../input/KeyHandler.hpp"

struct Control final {
    sf::Keyboard::Key forward_move;
    sf::Keyboard::Key backward_move;
    sf::Keyboard::Key left_move;
    sf::Keyboard::Key right_move;
    Control(const sf::Keyboard::Key forward, const sf::Keyboard::Key backward,
            const sf::Keyboard::Key left, const sf::Keyboard::Key right):
        forward_move(forward), backward_move(backward), left_move(left), right_move(right) { }
};

/**
 * Checks if there is a movement based on the provided control settings and key inputs.
 * @param control The Control object defining the key mappings.
 * @param key_handler The KeyHandler object providing the current key states.
 * @param length The length of the movement vector.
 * @param result The resulting vector storing the movement direction and length.
 * @return true if there is a valid movement, false otherwise.
 */
bool hasMovement(const Control &control, const KeyHandler &key_handler, float length, sf::Vector2f &result);