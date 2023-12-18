#pragma once

#include "BackgroundCreator.hpp"
#include "BoundaryCreator.hpp"
#include "../../additionally/SimpleCreators.hpp"
#include "../../quadtree/quadtree type defs/QuadtreeEl.hpp"

class RoomCreator final {
    sf::Vector2f _scale_factor;
    BoundaryCreator _boundary_creator;
    BackgroundCreator _background_creator;
    [[nodiscard]] int getBackgroundCountX(const int count_x) const;
    [[nodiscard]] int getBackgroundCountY(const int count_y) const;
public:
    RoomCreator(QuadtreeEl &quadtree, const BuildingData &building_data, SimpleCreators &simple_creators);

    /**
     * Creates a location with background and walls, considering the specified points and door openings.
     * @param p0 The starting point or left-top corner of the location.
     * @param p1 The ending point or right-bottom corner of the location.
     * @param door_opening The door opening configuration for the location.
     * @param room_type Specifies the type of the room.
     * @return A pointer to the created Location object.
     */
    [[nodiscard]] Location *create(const sf::Vector2i &p0, const sf::Vector2i &p1,
        const DoorOpeningMask door_opening, const RoomType room_type) const;
    /**
     * Creates a location with background and walls, considering the specified points and door openings.
     * @param p0 The starting point or left-top corner of the location.
     * @param count_x Amount of blocks in the x-direction.
     * @param count_y Amount of blocks in the y-direction.
     * @param door_opening The door opening configuration for the location.
     * @param room_type Specifies the type of the room.
     * @return A pointer to the created Location object.
     */
    [[nodiscard]] Location *create(const sf::Vector2i &p0, const int count_x, const int count_y,
        const DoorOpeningMask door_opening, const RoomType room_type) const;

    /**
     * Creates a vertical transition from the point p0 downward for a specified amount of blocks.
     * @param p0 The top-left transition point.
     * @param last_y Last Y-axis point.
     */
    void createVertTransition(sf::Vector2i p0, const int last_y) const;

    /**
     * Creates a horizontal transition from the point p0 to the right by the specified amount of blocks.
     * @param p0 The top-left transition point.
     * @param last_x Last X-axis point.
     */
    void createHorTransition(sf::Vector2i p0, const int last_x) const;

    const BoundaryCreator& getBoundaryCreator() const;
    
    ~RoomCreator() noexcept = default;
    RoomCreator(RoomCreator&&) noexcept = delete;
    RoomCreator& operator=(RoomCreator&&) noexcept = delete;
    RoomCreator(const RoomCreator&) noexcept = delete;
    RoomCreator& operator=(const RoomCreator&) noexcept = delete;
};