// ReSharper disable CppClangTidyHicppMultiwayPathsCovered CppDefaultCaseNotHandledInSwitchStatement
#include "../../../../include/game/entity/services/MovementUtils.hpp"

bool MovementUtils::hasMovement(const MovementMask movement_mask, float length, sf::Vector2f &result) {
    static constexpr float SQRT2 = 1.41421356f;
    switch (movement_mask) {
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