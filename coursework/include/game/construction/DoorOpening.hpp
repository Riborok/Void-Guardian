#pragma once
#include <array>
#include <SFML/System/Vector2.hpp>

typedef size_t DoorOpeningMask;

/**
 * The amount of distinct directions represented by the DoorOpening enum.
 */
constexpr DoorOpeningMask TOTAL_DIRECTIONS = 4;

/**
 * Constant representing a DoorOpeningMask with all four door openings (LEFT, RIGHT, TOP, BOTTOM) set.
 */
constexpr DoorOpeningMask ALL_DIRECTIONS_MASK = 1 << 0 | 1 << 1 | 1 << 2 | 1 << 3;

/**
 * Enumerates different door opening directions.
 * Each value represents a unique combination of openings in the left, right, top, and bottom directions.
 */
enum class DoorOpening final : DoorOpeningMask {
    NONE    = 0,
    LEFT    = 1 << 0,
    RIGHT   = 1 << 1,
    TOP     = 1 << 2,
    BOTTOM  = 1 << 3, 
};

extern const std::array<DoorOpening, TOTAL_DIRECTIONS> DOOR_OPENINGS;

/**
 * Converts a DoorOpening enum value to its equivalent DoorOpeningMask representation.
 * @param door_opening The DoorOpening value to be converted.
 * @return The corresponding DoorOpeningMask value.
 */
inline DoorOpeningMask doorToMask(const DoorOpening door_opening) {
    return static_cast<DoorOpeningMask>(door_opening);
}

/**
 * Gets the opposite door opening of the given DoorOpening.
 * @param door_opening The DoorOpening for which to get the opposite.
 * @return The opposite DoorOpening.
 * @throws std::invalid_argument if the DoorOpening type is invalid.
 */
DoorOpening getOppositeDoor(const DoorOpening door_opening);

/**
 * Moves the position in the specified direction.
 * @param door_opening The DoorOpening indicating the direction of movement.
 * @param pos The current position.
 * @return The new position after moving in the specified direction.
 * @throws std::invalid_argument if the DoorOpening type is invalid.
 */
sf::Vector2i movePosition(const DoorOpening door_opening, const sf::Vector2i &pos);

/**
 * Checks if the given DoorOpening represents a vertical door.
 * @param door_opening The DoorOpening value to check.
 * @return True if the door opening is vertical, false otherwise.
 * @throws std::invalid_argument if the DoorOpening type is invalid.
 */
bool isVert(const DoorOpening door_opening);

/**
 * Bitwise OR operator to combine two DoorOpening values, creating a new combined opening pattern.
 * @param operand1 The first DoorOpening value to combine.
 * @param operand2 The second DoorOpening value to combine.
 * @return A DoorOpening value representing the combination of the input openings.
 */
inline DoorOpeningMask operator|(const DoorOpening operand1, const DoorOpening operand2) {
    return doorToMask(operand1) | doorToMask(operand2);
}

/**
 * Bitwise OR operator to combine a DoorOpeningMask and a DoorOpening value, creating a new combined opening pattern.
 * @param operand1 The DoorOpeningMask value to combine.
 * @param operand2 The DoorOpening value to combine.
 * @return A DoorOpeningMask value representing the combination of the input openings.
 */
inline DoorOpeningMask operator|(const DoorOpeningMask operand1, const DoorOpening operand2) {
    return operand1 | doorToMask(operand2);
}

/**
 * Checks if the specified DoorOpening is present in the given DoorOpeningMask.
 * @param door_opening_mask The DoorOpeningMask to check.
 * @param door_opening The DoorOpening to check for.
 * @return True if the door opening is present, false otherwise.
 */
inline bool hasDoor(const DoorOpeningMask door_opening_mask, const DoorOpening door_opening) {
    return door_opening_mask & doorToMask(door_opening);
}

/**
 * Checks if the given DoorOpeningMask has a left door opening.
 * @param door_opening The DoorOpeningMask value to check.
 * @return True if the door opening is present, false otherwise.
 */
inline bool hasLeftDoor(const DoorOpeningMask door_opening) {
    return hasDoor(door_opening, DoorOpening::LEFT);
}

/**
 * Checks if the given DoorOpeningMask has a right door opening.
 * @param door_opening The DoorOpeningMask value to check.
 * @return True if the door opening is present, false otherwise.
 */
inline bool hasRightDoor(const DoorOpeningMask door_opening) {
    return hasDoor(door_opening, DoorOpening::RIGHT);
}

/**
 * Checks if the given DoorOpeningMask has a top door opening.
 * @param door_opening The DoorOpeningMask value to check.
 * @return True if the door opening is present, false otherwise.
 */
inline bool hasTopDoor(const DoorOpeningMask door_opening) {
    return hasDoor(door_opening, DoorOpening::TOP);
}

/**
 * Checks if the given DoorOpeningMask has a bottom door opening.
 * @param door_opening The DoorOpeningMask value to check.
 * @return True if the door opening is present, false otherwise.
 */
inline bool hasBottomDoor(const DoorOpeningMask door_opening) {
    return hasDoor(door_opening, DoorOpening::BOTTOM);
}