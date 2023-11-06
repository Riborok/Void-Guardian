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
    static constexpr size_t TYPE_DIGITS_DIVIDER = 1000;
    static constexpr size_t MAX_VALUE = UINT_MAX / TYPE_DIGITS_DIVIDER - 1;

    size_t _ids[Types::AMOUNT_OF_ELEMENT_TYPES + Types::AMOUNT_OF_OTHERS_TYPES] = {};
public:
    /**
     * Extracts the Type from the given ID.
     * @param id The object's unique identifier.
     * @return The Type component of the ID.
     */
    static Types::ElementTypes extractType(const size_t id) {
        return static_cast<Types::ElementTypes>(id % TYPE_DIGITS_DIVIDER);
    }

    /**
     * Checks if the object with the given ID corresponds to an animated type.
     * @param id The object's unique identifier.
     * @return True if the object is of an animated type, false otherwise.
     */
    static bool isAnimated(const size_t id) {
        return extractType(id) >= ANIMATED_TYPES_START;
    }

    /**
     * Checks if the object with the given ID corresponds to animation.
     * @param id The object's unique identifier.
     * @return True if the object is animation, false otherwise.
     */
    static bool isAnimation(const size_t id) {
        return extractType(id) >= ANIMATION_TYPES_START;
    }

    /**
     * Generates a unique ID for an object of a specific type.
     * @param type The type of the object (e.g., gun or wraith).
     * @return A unique ID based on the object's type.
     * @throws std::runtime_error if the maximum ID value is reached.
     */
    size_t generate(const Types::ElementTypes type) {
        return generate(static_cast<size_t>(type));
    }

    /**
     * Generates a unique ID for an object of a specific type.
     * @param type The type value of the object (e.g., gun or wraith).
     * @return A unique ID based on the object's type.
     * @throws std::runtime_error if the maximum ID value is reached.
     */
    size_t generate(const size_t type) {
        const size_t id = ++_ids[type];

        if (id >= MAX_VALUE)
            throw std::runtime_error("Maximum ID is reached.");
        return id * TYPE_DIGITS_DIVIDER + static_cast<size_t>(type);
    }

    IdTracker() noexcept = default;
    ~IdTracker() noexcept = default;
    
    IdTracker(const IdTracker&) noexcept = delete;
    IdTracker& operator=(const IdTracker&) noexcept = delete;
    IdTracker(IdTracker&&) noexcept = delete;
    IdTracker& operator=(IdTracker&&) noexcept = delete;
};