#pragma once
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
 * 0bRLBF
 */
typedef size_t MovementMask;
inline MovementMask getMovementMask(const Control &control, const KeyHandler &key_handler) {
    return  (key_handler.isKeyDown(control.forward_move)    << 0) +
            (key_handler.isKeyDown(control.backward_move)   << 1) +
            (key_handler.isKeyDown(control.left_move)       << 2) +
            (key_handler.isKeyDown(control.right_move)      << 3);
}