#pragma once
#include "DirectionGenerator.hpp"
#include "PositionalMap.hpp"
#include "LocationTransformation.hpp"
#include "RoomSizeManager.hpp"
#include "RoomTypeGenerator.hpp"
#include "../../GameField.hpp"
#include "../../../additionally/DefaultValues.hpp"

class GameFieldCreator final {
    typedef PositionalMap<LocationInfo> LocationInfoMap;
    
    RoomSizeManager _room_size_manager;
    DirectionGenerator _direction_generator;
    RoomTypeGenerator _room_type_generator;
    LocationInfoMap _location_map;

    size_t checkCoordinate(DoorOpeningMask &mask, const sf::Vector2i &pos,
        const int coord, const int critical_index, const DoorOpening door_opening) const;
    RoomType generateType();
    void createTransitions(LocationInfo &location_info, const DoorOpeningMask mask);
    [[nodiscard]] size_t getTotalObstacles(DoorOpeningMask &mask, const sf::Vector2i &pos) const;
    [[nodiscard]] DoorOpeningMask getDirections(const sf::Vector2i &pos);
    LocationInfo* createLocationInfo(const sf::Vector2i& next_pos, const RoomType room_type);
    void createNeighbors(LocationInfo* location_info);
    void initSpawnRoomPos(sf::Vector2i& pos, sf::Vector2i& next_pos, DoorOpening& neighbors_direction) const;
    void createRooms();
    [[nodiscard]] sf::Vector2f getStartPoint(const sf::Vector2i &block_delta) const;
public:
    explicit GameFieldCreator(const sf::Vector2i &last_index) noexcept;

    [[nodiscard]] GameField create(const int block_num, const int background_num,
        const sf::Vector2i &door_size_count = {DOOR_SIZE_COUNT, DOOR_SIZE_COUNT},
        const sf::Vector2f &block_scale = { BLOCK_SCALE, BLOCK_SCALE },
        const sf::Vector2f &background_scale = { BACKGROUND_SCALE, BACKGROUND_SCALE }) const;
    
    ~GameFieldCreator() noexcept;
    GameFieldCreator(GameFieldCreator&&) noexcept = delete;
    GameFieldCreator& operator=(GameFieldCreator&&) noexcept = delete;
    GameFieldCreator(const GameFieldCreator&) noexcept = delete;
    GameFieldCreator& operator=(const GameFieldCreator&) noexcept = delete;
};
