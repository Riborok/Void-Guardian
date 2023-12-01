// ReSharper disable CppClangTidyHicppMultiwayPathsCovered CppDefaultCaseNotHandledInSwitchStatement
#include "../../../../include/game/entity/player/Control.hpp"

typedef size_t MovementMask;
enum : MovementMask {
    NONE = 0,
    FORWARD = 1 << 0,
    BACKWARD = 1 << 1,
    LEFT = 1 << 2,
    RIGHT = 1 << 3
};

MovementMask getMovementMask(const Control &control, const KeyHandler &key_handler) {
    return  (key_handler.isKeyDown(control.forward_move) << 0) +
            (key_handler.isKeyDown(control.backward_move) << 1) +
            (key_handler.isKeyDown(control.left_move) << 2) +
            (key_handler.isKeyDown(control.right_move) << 3);
}

constexpr float SQRT2 = 1.41421356f;

bool hasMovement(const Control &control, const KeyHandler &key_handler, float length, sf::Vector2f &result) {
    switch (getMovementMask(control, key_handler)) {
    case NONE:
    case FORWARD | BACKWARD | LEFT | RIGHT:
    case LEFT | RIGHT:
    case FORWARD | BACKWARD:
        return false;

    case FORWARD:
    case FORWARD | RIGHT | LEFT:
        result = {0, -length};
        break;

    case BACKWARD:
    case BACKWARD | RIGHT | LEFT:
        result = {0, length};
        break;

    case LEFT:
    case LEFT | FORWARD | BACKWARD:
        result = {-length, 0};
        break;

    case RIGHT:
    case RIGHT | FORWARD | BACKWARD:
        result = {length, 0};
        break;

    case FORWARD | LEFT:
        length /= SQRT2;
        result = {-length, -length};
        break;

    case FORWARD | RIGHT:
        length /= SQRT2;
        result = {length, -length};
        break;

    case BACKWARD | LEFT:
        length /= SQRT2;
        result = {-length, length};
        break;

    case BACKWARD | RIGHT:
        length /= SQRT2;
        result = {length, length};
        break;
    }
    return true;
}