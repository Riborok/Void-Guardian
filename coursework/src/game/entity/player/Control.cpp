#include "../../../../include/game/entity/player/Control.hpp"

MovementUtils::MovementMask Control::getMovementMask(const InputHandler &input_handler) const {
    return  (input_handler.isDown(forward_move) << 0) +
            (input_handler.isDown(backward_move) << 1) +
            (input_handler.isDown(left_move) << 2) +
            (input_handler.isDown(right_move) << 3);
}