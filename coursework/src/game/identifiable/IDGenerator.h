#pragma once

#include <climits>
#include <stdexcept>

#include "../../additionally/Types.h"

/**
 * ID Generator
 * 
 * In the context of object identification, we use two components to form a unique identifier (ID):
 * 1. Type: The first two digits represent the character or representation of the object (e.g., sprite, model, element).
 *    These digits classify the object based on its fundamental characteristics.
 * 2. UniqueID: A unique identifier (with no range limitation) distinguishes one object from another.
 *    It ensures that each object within the same character and type category has a distinct identity.
 * When combined, these components form a complete and unique identification for objects within a system.
 */
class IdGenerator final {
    enum : unsigned int {
        TYPE_DIGITS_DIVIDER = 1000u,
        MAX_VALUE = UINT_MAX / TYPE_DIGITS_DIVIDER - 1u
    };

    unsigned int _ids[Types::AMOUNT_OF_ELEMENT_TYPE] = {};
public:
    /**
     * Extracts the Type from the given ID.
     * @param id The object's unique identifier.
     * @return The Type component of the ID.
     */
    static Types::ElementType extractType(const unsigned int id) {
        return static_cast<Types::ElementType>(id % TYPE_DIGITS_DIVIDER);
    }

    /**
     * Generates a unique ID for an object of a specific type.
     * @param type The type of the object (e.g., gun or wraith).
     * @return A unique ID based on the object's type.
     * @throws std::runtime_error if the maximum ID value is reached.
     */
    unsigned int generate(const Types::ElementType type) {
        const unsigned int id = ++_ids[type];

        if (id >= MAX_VALUE)
            throw std::runtime_error("Maximum ID is reached.");
        return id * TYPE_DIGITS_DIVIDER + type;
    }

    IdGenerator() noexcept = default;
    ~IdGenerator() noexcept = default;
    
    IdGenerator(const IdGenerator&) noexcept = delete;
    IdGenerator& operator=(const IdGenerator&) noexcept = delete;
    IdGenerator(IdGenerator&&) noexcept = delete;
    IdGenerator& operator=(IdGenerator&&) noexcept = delete;
};