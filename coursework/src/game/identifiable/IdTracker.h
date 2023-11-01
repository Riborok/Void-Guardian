#pragma once

#include <climits>
#include <stdexcept>

#include "../../additionally/Types.h"

/**
 * ID Tracker
 * 
 * In the context of object identification, we use two components to form a unique identifier (ID):
 * 1. Type: The first two digits represent the character or representation of the object (e.g., sprite, model, element).
 *    These digits classify the object based on its fundamental characteristics.
 * 2. UniqueID: A unique identifier (with no range limitation) distinguishes one object from another.
 *    It ensures that each object within the same character and type category has a distinct identity.
 * When combined, these components form a complete and unique identification for objects within a system.
 */
class IdTracker final {
    enum : unsigned int {
        TYPE_DIGITS_DIVIDER = 1000u,
        MAX_VALUE = UINT_MAX / TYPE_DIGITS_DIVIDER - 1u
    };

    unsigned int _ids[Types::AMOUNT_OF_ELEMENT_TYPES] = {};
public:
    /**
     * Extracts the Type from the given ID.
     * @param id The object's unique identifier.
     * @return The Type component of the ID.
     */
    static Types::ElementTypes extractType(const unsigned int id) {
        return static_cast<Types::ElementTypes>(id % TYPE_DIGITS_DIVIDER);
    }

    /**
     * Checks if the object with the given ID corresponds to an animated type.
     * @param id The object's unique identifier.
     * @return True if the object is of an animated type, false otherwise.
     */
    static bool isAnimated(const unsigned int id) {
        return extractType(id) >= ANIMATED_TYPES_START;
    }

    /**
     * Checks if the object with the given ID corresponds to animation.
     * @param id The object's unique identifier.
     * @return True if the object is animation, false otherwise.
     */
    static bool isAnimation(const unsigned int id) {
        return extractType(id) >= ANIMATION_TYPES_START;
    }

    /**
     * Generates a unique ID for an object of a specific type.
     * @param type The type of the object (e.g., gun or wraith).
     * @return A unique ID based on the object's type.
     * @throws std::runtime_error if the maximum ID value is reached.
     */
    unsigned int generate(const Types::ElementTypes type) {
        const unsigned int id = ++_ids[type];

        if (id >= MAX_VALUE)
            throw std::runtime_error("Maximum ID is reached.");
        return id * TYPE_DIGITS_DIVIDER + type;
    }

    IdTracker() noexcept = default;
    ~IdTracker() noexcept = default;
    
    IdTracker(const IdTracker&) noexcept = delete;
    IdTracker& operator=(const IdTracker&) noexcept = delete;
    IdTracker(IdTracker&&) noexcept = delete;
    IdTracker& operator=(IdTracker&&) noexcept = delete;
};