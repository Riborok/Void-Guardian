#pragma once
#include <random>
#include <SFML/System/Vector2.hpp>

#include "BuildingData.hpp"
#include "DoorOpening.hpp"
#include "Location.hpp"
#include "LocationCreator.hpp"
#include "../../additionally/SimpleCreators.hpp"

class BoundaryCreator final {
    static constexpr int MIN_CLOSING_BLOCK = 4;
    static constexpr int MAX_CLOSING_BLOCK = 9;
    mutable std::uniform_int_distribution<int> _missed_blocks_num{MIN_CLOSING_BLOCK, MAX_CLOSING_BLOCK};
    
    BoundaryData _building_data;
    QuadtreeEl *_quadtree;
    SimpleCreators *_simple_creators;
    sf::Vector2i _door_size;

    void createMissedBlock(const int x, const int y, Location *location) const;
 
    void createHorMissedBlocks(int start_x, const int last_x, const int y, Location *location) const;
    void createVertMissedBlocks(int start_y, const int last_y, const int x, Location *location) const;
    
    void createHorBoundaryWithDoor(const sf::Vector2i &p, const int last, Location *location, const int door_size) const;
    void createVertBoundaryWithDoor(const sf::Vector2i &p, const int last, Location *location, const int door_size) const;
public:
    BoundaryCreator(const BoundaryData &building_data, QuadtreeEl &quadtree, SimpleCreators &simple_creators);

    /**
     * Creates a block at the specified position.
     * @param pos The position (sf::Vector2f) of the block.
     */
    void createBlock(const sf::Vector2f &pos) const;
 
    /**
     * Creates a horizontal boundary of elements between two x-coordinates, allowing customization of offsets.
     * @param start_x The x-coordinate of the starting point of the boundary.
     * @param last_x The x-coordinate of the ending point of the boundary.
     * @param y The y-coordinate at which the boundary is created.
     */
    void createHorBoundary(int start_x, const int last_x, const int y) const;

    /**
     * Creates a vertical boundary of elements between two y-coordinates, allowing customization of offsets.
     * @param start_y The y-coordinate of the starting point of the boundary.
     * @param last_y The y-coordinate of the ending point of the boundary.
     * @param x The x-coordinate at which the boundary is created.
     */
    void createVertBoundary(int start_y, const int last_y, const int x) const;

    /**
     * Creates a boundary of elements between two points, allowing customization of offsets.
     * @param p0 The starting point of the boundary.
     * @param p1 The ending point of the boundary.
     * @param door_opening Specifies the opening direction of the door (if any).
     * @param room_type Specifies the type of the room.
     * @return A pointer to the created Location object representing the boundary and missed blocks.
     */
    [[nodiscard]] Location *createLocation(const sf::Vector2i &p0, const sf::Vector2i &p1,
        const DoorOpeningMask door_opening, const RoomType room_type) const;
    
    /**
     * Creates a boundary of elements based on a starting point and the amount of elements along the X and Y axes,
     * allowing customization of offsets.
     * @param p0 The starting point of the boundary.
     * @param count_x The amount of elements along the X-axis.
     * @param count_y The amount of elements along the Y-axis.
     * @param door_opening Specifies the opening direction of the door (if any).
     * @param room_type Specifies the type of the room.
     * @return A pointer to the created Location object representing the boundary and missed blocks.
     */
    [[nodiscard]] Location *createLocation(const sf::Vector2i &p0, const int count_x, const int count_y,
        const DoorOpeningMask door_opening, const RoomType room_type) const;

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
    [[nodiscard]] const sf::Vector2i &getDoorSizeCount() const;
    
    ~BoundaryCreator() noexcept = default;
    BoundaryCreator(BoundaryCreator&&) noexcept = delete;
    BoundaryCreator& operator=(BoundaryCreator&&) noexcept = delete;
    BoundaryCreator(const BoundaryCreator&) noexcept = delete;
    BoundaryCreator& operator=(const BoundaryCreator&) noexcept = delete;
};