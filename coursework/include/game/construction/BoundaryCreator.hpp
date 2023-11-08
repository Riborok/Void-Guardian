﻿#pragma once
#include <random>
#include <SFML/System/Vector2.hpp>

#include "DoorOpening.hpp"
#include "Location.hpp"
#include "../../additionally/TypesDef.hpp"

class BoundaryCreator final {
    static constexpr int MIN_CLOSING_BLOCK = 4;
    static constexpr int MAX_CLOSING_BLOCK = 9;
    std::uniform_int_distribution<int> _missed_blocks_num{MIN_CLOSING_BLOCK, MAX_CLOSING_BLOCK};
    
    int _num;
    sf::Vector2f _scale;
    sf::Vector2i _delta;
    sf::Vector2i _door_size;
    QuadtreeEl *_quadtree;

    [[nodiscard]] int createHorBoundary(int coord, const int last, const int y) const;
    [[nodiscard]] int createVertBoundary(int coord, const int last, const int x) const;
    
    [[nodiscard]] int createHorMissedBlocks(int coord, const int last, const int y, Location *location);
    [[nodiscard]] int createVertMissedBlocks(int coord, const int last, const int x, Location *location);
    void createHorBoundaryWithDoor(const sf::Vector2i &p, const int last, Location *location, const int door_size);
    void createVertBoundaryWithDoor(const sf::Vector2i &p, const int last, Location *location, const int door_size);
public:
    BoundaryCreator(const int num, const sf::Vector2f &scale, const sf::Vector2i &door_count_size, QuadtreeEl &quadtree);

    /**
     * Creates a boundary of elements between two points, allowing customization of offsets.
     * @param p0 The starting point of the boundary.
     * @param p1 The ending point of the boundary.
     * @return A pointer to the created Location object representing the boundary and missed blocks.
     * @param door_opening Specifies the opening direction of the door (if any).
     */
    [[nodiscard]] Location *createLocation(const sf::Vector2i &p0, const sf::Vector2i &p1,
        const DoorOpeningMask door_opening);
    
    /**
     * Creates a boundary of elements based on a starting point and the amount of elements along the X and Y axes,
     * allowing customization of offsets.
     * @param p0 The starting point of the boundary.
     * @param count_x The amount of elements along the X-axis.
     * @param count_y The amount of elements along the Y-axis.
     * @return A pointer to the created Location object representing the boundary and missed blocks.
     * @param door_opening Specifies the opening direction of the door (if any).
     */
    [[nodiscard]] Location *createLocation(const sf::Vector2i &p0, const int count_x, const int count_y,
        const DoorOpeningMask door_opening);

    /**
     * Creates a vertical transition from the point p0 downward for a specified amount of blocks.
     * @param p0 The top-left transition point.
     * @param last_y Last Y-axis point.
     * @return The last X-axis point after creating the vertical transition.
     */
    [[nodiscard]] int createVertTransition(const sf::Vector2i &p0, const int last_y) const;

    /**
     * Creates a horizontal transition from the point p0 to the right by the specified amount of blocks.
     * @param p0 The top-left transition point.
     * @param last_x Last X-axis point.
     * @return The last Y-axis point after creating the horizontal transition.
     */
    [[nodiscard]] int createHorTransition(const sf::Vector2i &p0, const int last_x) const;

    [[nodiscard]] const sf::Vector2i &getDelta() const;
    
    ~BoundaryCreator() noexcept = default;
    BoundaryCreator(BoundaryCreator&&) noexcept = delete;
    BoundaryCreator& operator=(BoundaryCreator&&) noexcept = delete;
    BoundaryCreator(const BoundaryCreator&) noexcept = delete;
    BoundaryCreator& operator=(const BoundaryCreator&) noexcept = delete;
};
