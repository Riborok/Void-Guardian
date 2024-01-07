#include "../../../../include/game/entity/player/Control.hpp"

MovementUtils::MovementMask Control::getMovementMask() const {
    return  (forward_move.idPressed() << 0)  +
            (backward_move.idPressed() << 1) +
            (left_move.idPressed() << 2)     +
            (right_move.idPressed() << 3);
}