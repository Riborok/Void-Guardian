#pragma once
#include <array>

typedef size_t DoorOpeningMask;

constexpr size_t AMOUNT_OF_DIRECTIONS = 4;
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

/**
 * Gets the serial number representing the position of the door opening in a specific order.
 * This order should be followed when designing doorways in arrays or other structures.
 * @param door_opening The DoorOpening value for which to get the serial number.
 * @return The serial number representing the position of the door opening.
 * @throws std::invalid_argument if the DoorOpening type is invalid.
 */
size_t getSerialNumber(const DoorOpening door_opening);

extern const std::array<DoorOpening, AMOUNT_OF_DIRECTIONS> DOOR_OPENINGS;

/**
 * Gets the opposite door opening of the given DoorOpening.
 * @param door_opening The DoorOpening for which to get the opposite.
 * @return The opposite DoorOpening.
 * @throws std::invalid_argument if the DoorOpening type is invalid.
 */
DoorOpening getOppositeDoor(const DoorOpening door_opening);

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
    return static_cast<DoorOpeningMask>(operand1) | static_cast<DoorOpeningMask>(operand2);
}

/**
 * Bitwise OR operator to combine a DoorOpeningMask and a DoorOpening value, creating a new combined opening pattern.
 * @param operand1 The DoorOpeningMask value to combine.
 * @param operand2 The DoorOpening value to combine.
 * @return A DoorOpeningMask value representing the combination of the input openings.
 */
inline DoorOpeningMask operator|(const DoorOpeningMask operand1, const DoorOpening operand2) {
    return operand1 | static_cast<DoorOpeningMask>(operand2);
}

/**
 * Checks if the specified DoorOpening is present in the given DoorOpeningMask.
 * @param door_opening_mask The DoorOpeningMask to check.
 * @param door_opening The DoorOpening to check for.
 * @return True if the door opening is present, false otherwise.
 */
inline bool hasDoor(const DoorOpeningMask door_opening_mask, const DoorOpening door_opening) {
    return door_opening_mask & static_cast<size_t>(door_opening);
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