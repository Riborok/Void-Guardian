#pragma once

#include "Element.hpp"
#include "ReplaceableElement.hpp"
#include "../additionally/Types.hpp"

namespace ElementCreation {
    
    /**
     * Create an element with specified properties.
     * @param point The position of the element.
     * @param angle The rotation angle of the element.
     * @param type The type of the element.
     * @param num The element number.
     * @param scale The scaling factor for the element (default is 1.0).
     * @return A pointer to the newly created Element.
     * @note Memory is allocated for the Element, and it is the caller's responsibility to free this memory.
     */
    Element *create(const sf::Vector2f &point, const float angle, const Types::ElementTypes type, const int num,
            const sf::Vector2f &scale = {1.0f, 1.0f});
    /**
     * Create a replaceable element with specified properties.
     * @param point The position of the element.
     * @param angle The rotation angle of the element.
     * @param type The type of the element.
     * @param num The element number.
     * @param scale The scaling factor for the element (default is 1.0).
     * @return A pointer to the newly created ReplaceableElement.
     * @note Memory is allocated for the ReplaceableElement, and it is the caller's responsibility to free this memory.
     */
    ReplaceableElement *createReplaceable(const sf::Vector2f &point, const float angle,
            const Types::ElementTypes type, const int num, const sf::Vector2f &scale = {1.0f, 1.0f});
}