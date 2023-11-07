#pragma once
#include <SFML/System/Vector2.hpp>

#include "Location.hpp"
#include "../../element/ElementCreation.hpp"
#include "../../Quadtree/Quadtree.hpp"

namespace MapCreation {
    /**
     * Enumerates different door opening directions.
     * Each value represents a unique combination of openings in the left, right, top, and bottom directions.
     */
    enum class DoorOpening {
        NONE    = 0b0000,
        LEFT    = 0b0001,
        RIGHT   = 0b0010,
        TOP     = 0b0100,
        BOTTOM  = 0b1000,
    };
    /**
     * Bitwise OR operator to combine two DoorOpening values, creating a new combined opening pattern.
     * @param operand1 The first DoorOpening value to combine.
     * @param operand2 The second DoorOpening value to combine.
     * @return A DoorOpening value representing the combination of the input openings.
     */
    DoorOpening operator|(DoorOpening operand1, DoorOpening operand2);

    /**
     * Creates a background grid of elements in a specified region.
     * @param num The element's identifier.
     * @param p0 The starting point of the grid.
     * @param p1 The ending point of the grid.
     * @param quadtree The Quadtree data structure to insert elements into.
     * @param scale The scaling factor for the elements.
     */
    void createBackground(const int num, const sf::Vector2u &p0, const sf::Vector2u &p1,
            Quadtree<Element> &quadtree, const sf::Vector2f &scale);
    /**
     * Creates a background grid of elements using a starting point and the number of elements along the X and Y axes.
     * @param num The element's identifier.
     * @param p0 The starting point of the grid.
     * @param count_x The amount of elements along the X-axis.
     * @param count_y The amount of elements along the Y-axis.
     * @param quadtree The Quadtree data structure to insert elements into.
     * @param scale The scaling factor for the elements.
     */
    void createBackground(const int num, const sf::Vector2u &p0, const unsigned count_x, const unsigned count_y,
            Quadtree<Element> &quadtree, const sf::Vector2f &scale);

    /**
     * Creates a boundary of elements between two points, allowing customization of offsets.
     * @param num The element's identifier.
     * @param p0 The starting point of the boundary.
     * @param p1 The ending point of the boundary.
     * @param scale The scaling factor for the elements.
     * @param door_opening Specifies the opening direction of the door (if any).
     * @param quadtree The Quadtree data structure to insert elements into.
     * @param offset_x The horizontal offset for the door.
     * @param offset_y The vertical offset for the door.
     * @return A pointer to the created Location object representing the boundary and missed blocks.
     */
    Location *createLocation(const int num, const sf::Vector2u &p0, const sf::Vector2u &p1,
            const sf::Vector2f &scale, const DoorOpening door_opening,
            Quadtree<Element> &quadtree,
            const unsigned offset_x = 0, const unsigned offset_y = 0);
    /**
     * Creates a boundary of elements based on a starting point and the number of elements along the X and Y axes,
     * allowing customization of offsets.
     * @param num The element's identifier.
     * @param p0 The starting point of the boundary.
     * @param count_x The amount of elements along the X-axis.
     * @param count_y The amount of elements along the Y-axis.
     * @param scale The scaling factor for the elements.
     * @param door_opening Specifies the opening direction of the door (if any).
     * @param quadtree The Quadtree data structure to insert elements into.
     * @param amount_offset_x The horizontal offset for the door based on the amount of elements.
     * @param amount_offset_y The vertical offset for the door based on the amount of elements.
     * @return A pointer to the created Location object representing the boundary and missed blocks.
     */
    Location *createLocation(const int num, const sf::Vector2u &p0, const unsigned count_x, const unsigned count_y,
            const sf::Vector2f &scale, const DoorOpening door_opening,
            Quadtree<Element> &quadtree,
            const unsigned amount_offset_x = 0, const unsigned amount_offset_y = 0);
}