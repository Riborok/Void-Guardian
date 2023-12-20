#pragma once
#include "DirectionGenerator.hpp"
#include "LocationTransformation.hpp"
#include "portal/PortalData.hpp"
#include "RoomSizeManager.hpp"
#include "RoomTypeGenerator.hpp"
#include "../../GameField.hpp"
#include "../../../additionally/SimpleCreators.hpp"
#include "../../entity/component/gun/GunManager.hpp"

class GameFieldCreator final {
    static constexpr size_t START_INDEX = 1;
    typedef SequentialArray2D<LocationInfo*> LocationInfoMap;

    size_t _lvl;
    RoomSizeManager _room_size_manager;
    DirectionGenerator _direction_generator;
    RoomTypeGenerator _room_type_generator;
    LocationInfoMap _location_info_map;
    size_t _min_quantity;

    sf::Vector2i getLatestMapIndex() const;
    size_t checkCoordinate(DoorOpeningMask &mask, const sf::Vector2i &pos,
        const int coord, const int critical_index, const DoorOpening door_opening) const;
    RoomType generateType();
    void createTransitions(LocationInfo &location_info, const DoorOpeningMask mask) noexcept(false);
    [[nodiscard]] size_t getTotalObstacles(DoorOpeningMask &mask, const sf::Vector2i &pos) const;
    [[nodiscard]] DoorOpeningMask getDirections(const sf::Vector2i &pos) const;
    LocationInfo* createLocationInfo(const sf::Vector2i& next_pos, const RoomType room_type);
    void createNeighbors(LocationInfo* location_info);
    void initSpawnRoomPos(sf::Vector2i& pos, sf::Vector2i& next_pos, DoorOpening& neighbors_direction) const;
    void createRooms();
    void addExtraRooms();
    [[nodiscard]] sf::Vector2f getStartPoint(const sf::Vector2i &block_delta) const;
public:
    explicit GameFieldCreator(const size_t lvl) noexcept;

    [[nodiscard]] GameField initialize(const BoundaryInfo &boundary_info) const;
    void create(GameField& game_field, const BuildingInfo &building_info, GunManager &gun_manager,
        SimpleCreators &simple_creators, const InOutPortals& portals_data) const;
    
    ~GameFieldCreator() noexcept;
    GameFieldCreator(GameFieldCreator&&) noexcept = delete;
    GameFieldCreator& operator=(GameFieldCreator&&) noexcept = delete;
    GameFieldCreator(const GameFieldCreator&) noexcept = delete;
    GameFieldCreator& operator=(const GameFieldCreator&) noexcept = delete;
};
