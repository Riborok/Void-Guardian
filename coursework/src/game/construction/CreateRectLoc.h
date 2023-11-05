#pragma once
#include <SFML/System/Vector2.hpp>

#include "../../element/ElementCreation.h"
#include "../../Quadtree/Quadtree.h"

namespace CreateRectLoc {
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
    inline DoorOpening operator|(DoorOpening operand1, DoorOpening operand2) {
        return static_cast<DoorOpening>(static_cast<int>(operand1) | static_cast<int>(operand2));
    }
    
    namespace InnerLogic {
        inline unsigned insertHorizontalBlocks(unsigned coord, const unsigned last, const unsigned y,
                const int num, const sf::Vector2f &scale, const unsigned delta, Quadtree<Element> &quadtree) {
            while (coord < last) {
                quadtree.insert(ElementCreation::create({static_cast<float>(coord), static_cast<float>(y)},
                    0, Types::ElementTypes::BLOCK, num, scale));
                coord += delta;
            }
            return coord;
        }
        inline unsigned insertVerticalBlocks(unsigned coord, const unsigned last, const unsigned x,
                const int num, const sf::Vector2f &scale, const unsigned delta, Quadtree<Element> &quadtree) {
            while (coord < last) {
                quadtree.insert(ElementCreation::create({static_cast<float>(x), static_cast<float>(coord)},
                    0, Types::ElementTypes::BLOCK, num, scale));
                coord += delta;
            }
            return coord;
        }
        inline void createHorBoundary(const int num, const sf::Vector2u &p, const unsigned last, Quadtree<Element> &quadtree,
                                             const sf::Vector2f &scale, const unsigned delta, const unsigned offset) {
            unsigned coord = p.x;
            const unsigned last_offset = (p.x + last - offset) / 2;

            coord = insertHorizontalBlocks(coord, last_offset, p.y, num, scale, delta, quadtree);
            coord += offset;
            insertHorizontalBlocks(coord, last, p.y, num, scale, delta, quadtree);
        }
        inline void createVertBoundary(const int num, const sf::Vector2u &p, const unsigned last, Quadtree<Element> &quadtree,
                                           const sf::Vector2f &scale, const unsigned delta, const unsigned offset) {
            unsigned coord = p.y;
            const unsigned last_offset = (p.y + last - offset) / 2;

            coord = insertVerticalBlocks(coord, last_offset, p.x, num, scale, delta, quadtree);
            coord += offset;
            insertVerticalBlocks(coord, last, p.x, num, scale, delta, quadtree);
        }
        inline bool isLeft(const DoorOpening door_opening) { return static_cast<int>(door_opening) & static_cast<int>(DoorOpening::LEFT); }
        inline bool isRight(const DoorOpening door_opening) { return static_cast<int>(door_opening) & static_cast<int>(DoorOpening::RIGHT); }
        inline bool isTop(const DoorOpening door_opening) { return static_cast<int>(door_opening) & static_cast<int>(DoorOpening::TOP); }
        inline bool isBottom(const DoorOpening door_opening) { return static_cast<int>(door_opening) & static_cast<int>(DoorOpening::BOTTOM); }

        inline sf::Vector2u getDelta(const sf::Vector2u &size, const sf::Vector2f &scale) {
            return {
                static_cast<unsigned>(static_cast<float>(size.x) * scale.x),
                static_cast<unsigned>(static_cast<float>(size.y) * scale.y)
            };
        }
    }

    /**
     * Creates a background grid of elements in a specified region.
     * @param num The element's identifier.
     * @param p0 The starting point of the grid.
     * @param p1 The ending point of the grid.
     * @param quadtree The Quadtree data structure to insert elements into.
     * @param scale The scaling factor for the elements.
     */
    inline void createBackground(const int num, const sf::Vector2u &p0, const sf::Vector2u &p1,
            Quadtree<Element> &quadtree, const sf::Vector2f &scale) {
        const auto delta = InnerLogic::getDelta(Constants::BACKGROUND_SIZE, scale);
        
        unsigned y = p0.y;
        while (y < p1.y) {
            unsigned x = p0.x;
            while (x < p1.x) {
                quadtree.insert(ElementCreation::create({static_cast<float>(x), static_cast<float>(y)},
                    0, Types::ElementTypes::BACKGROUND, num, scale));
                x += delta.x;
            }
            y += delta.y;
        }
    }
    /**
     * Creates a background grid of elements using a starting point and the number of elements along the X and Y axes.
     * @param num The element's identifier.
     * @param p0 The starting point of the grid.
     * @param count_x The amount of elements along the X-axis.
     * @param count_y The amount of elements along the Y-axis.
     * @param quadtree The Quadtree data structure to insert elements into.
     * @param scale The scaling factor for the elements.
     */
    inline void createBackground(const int num, const sf::Vector2u &p0, const unsigned count_x, const unsigned count_y,
            Quadtree<Element> &quadtree, const sf::Vector2f &scale) {
        const auto delta = InnerLogic::getDelta(Constants::BACKGROUND_SIZE, scale);
        const sf::Vector2u p1(p0.x + delta.x * count_x,p0.y + delta.y * count_y);
        createBackground(num, p0, p1, quadtree, scale);
    }

    /**
     * Creates a boundary of elements between two points, allowing customization of offsets.
     * @param num The element's identifier.
     * @param p0 The starting point of the boundary.
     * @param p1 The ending point of the boundary.
     * @param quadtree The Quadtree data structure to insert elements into.
     * @param scale The scaling factor for the elements.
     * @param door_opening Specifies the opening direction of the door (if any).
     * @param offset_x The horizontal offset for the door.
     * @param offset_y The vertical offset for the door.
     */
    inline void createBoundary(const int num, const sf::Vector2u &p0, const sf::Vector2u &p1,
            Quadtree<Element> &quadtree, const sf::Vector2f &scale, const DoorOpening door_opening,
            const unsigned offset_x = 0, const unsigned offset_y = 0) {
        const auto delta = InnerLogic::getDelta(Constants::BLOCK_SIZE, scale);
        const unsigned start_y = p0.y + delta.y;
        const unsigned last_y = p1.y - delta.y;
        const unsigned last_x = p1.x - delta.x;

        InnerLogic::createHorBoundary(num, p0, p1.x, quadtree, scale, delta.x,
            InnerLogic::isTop(door_opening) ? offset_x : 0);
        InnerLogic::createHorBoundary(num, {p0.x, last_y}, p1.x, quadtree, scale, delta.x,
            InnerLogic::isBottom(door_opening) ? offset_x : 0);

        InnerLogic::createVertBoundary(num, {p0.x, start_y}, last_y, quadtree, scale, delta.y,
            InnerLogic::isLeft(door_opening) ? offset_y : 0);
        InnerLogic::createVertBoundary(num, {last_x, start_y}, last_y, quadtree, scale, delta.y,
            InnerLogic::isRight(door_opening) ? offset_y : 0);
    }
    /**
     * Creates a boundary of elements based on a starting point and the number of elements along the X and Y axes,
     * allowing customization of offsets.
     * @param num The element's identifier.
     * @param p0 The starting point of the boundary.
     * @param count_x The amount of elements along the X-axis.
     * @param count_y The amount of elements along the Y-axis.
     * @param quadtree The Quadtree data structure to insert elements into.
     * @param scale The scaling factor for the elements.
     * @param door_opening Specifies the opening direction of the door (if any).
     * @param amount_offset_x The horizontal offset for the door based on the amount of elements.
     * @param amount_offset_y The vertical offset for the door based on the amount of elements.
     */
    inline void createBoundary(const int num, const sf::Vector2u &p0, const unsigned count_x, const unsigned count_y,
            Quadtree<Element> &quadtree, const sf::Vector2f &scale, const DoorOpening door_opening,
            const unsigned amount_offset_x = 0, const unsigned amount_offset_y = 0) {
        const auto delta = InnerLogic::getDelta(Constants::BLOCK_SIZE, scale);
        const sf::Vector2u p1(p0.x + delta.x * count_x, p0.y + delta.y * count_y);
        createBoundary(num, p0, p1, quadtree, scale, door_opening, amount_offset_x * delta.x, amount_offset_y * delta.y);
    }
}
