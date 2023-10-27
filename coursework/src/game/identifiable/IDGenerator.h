// ReSharper disable CppClangTidyModernizeMacroToEnum
#pragma once

#define CHARACTER_DIGITS 100
#define TYPE_DIGITS 100

/**
 * ID Generator
 * 
 * In the context of object identification, we use three components to form a unique identifier (ID):
 * 1. Character: The first two digits represent the character or representation of the object (e.g., sprite, model, element).
 *    These digits classify the object based on its fundamental characteristics.
 * 2. Type: The next two digits specify the type of the object.
 *    These digits categorize the object within its character representation (e.g., character-specific type).
 * 3. UniqueID: A unique identifier (with no range limitation) distinguishes one object from another.
 *    It ensures that each object within the same character and type category has a distinct identity.
 * When combined, these components form a complete and unique identification for objects within a system.
 */
class IdGenerator {
public:
    /**
     * Extracts the Character from the given ID.
     * @param id The object's unique identifier.
     * @return The Character component of the ID.
     */
    static unsigned int extractCharacter(const unsigned int id) {
        return id % CHARACTER_DIGITS;
    }

    /**
     * Extracts the Type from the given ID.
     * @param id The object's unique identifier.
     * @return The Type component of the ID.
     */
    static unsigned int extractType(const unsigned int id) {
        return id / CHARACTER_DIGITS % TYPE_DIGITS;
    }
};