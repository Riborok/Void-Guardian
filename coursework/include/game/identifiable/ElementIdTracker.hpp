#pragma once

#include "../../additionally/ElementType.hpp"

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
class ElementIdTracker final {
    static constexpr size_t TYPE_DIGITS_DIVIDER = 1000;
    static constexpr size_t MAX_VALUE = SIZE_MAX / TYPE_DIGITS_DIVIDER - 1;

    size_t _ids[ELEMENT_TYPES_COUNT] = {};
public:
    /**
     * Extracts the Type from the given ID.
     * @param id The object's unique identifier.
     * @return The Type component of the ID.
     */
    static ElementTypes extractType(const size_t id);

    /**
     * Checks if the object with the given ID corresponds to an animated type.
     * @param id The object's unique identifier.
     * @return True if the object is of an animated type, false otherwise.
     */
    static bool isAnimated(const size_t id);

    /**
     * Checks if the object with the given ID corresponds to animation.
     * @param id The object's unique identifier.
     * @return True if the object is animation, false otherwise.
     */
    static bool isAnimation(const size_t id);

    /**
     * Generates a unique ID for an object of a specific type.
     * @param type The type of the object (e.g., gun or wraith).
     * @return A unique ID based on the object's type.
     * @throws std::runtime_error if the maximum ID value is reached.
     */
    size_t generate(const ElementTypes type);

    /**
     * Generates a unique ID for an object of a specific type.
     * @param type The type value of the object (e.g., gun or wraith).
     * @return A unique ID based on the object's type.
     * @throws std::runtime_error if the maximum ID value is reached.
     */
    size_t generate(const size_t type);

    ElementIdTracker() noexcept = default;
    ~ElementIdTracker() noexcept = default;
    
    ElementIdTracker(const ElementIdTracker&) noexcept = delete;
    ElementIdTracker& operator=(const ElementIdTracker&) noexcept = delete;
    ElementIdTracker(ElementIdTracker&&) noexcept = delete;
    ElementIdTracker& operator=(ElementIdTracker&&) noexcept = delete;
};