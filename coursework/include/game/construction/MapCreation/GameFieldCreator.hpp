#pragma once
#include "LocationInfoMap.hpp"
#include "LocationTransformation.hpp"
#include "RoomSizeManager.hpp"
#include "../../GameField.hpp"
#include "../../../additionally/DefaultValues.hpp"

class GameFieldCreator final {
    RoomSizeManager _loc_size;
    LocationInfoMap _location_map;
    LocationInfo _root;

    [[nodiscard]] LocationInfo createRoot();
    [[nodiscard]] sf::Vector2f getStartPoint(const sf::Vector2i &block_delta) const;
public:
    GameFieldCreator() noexcept;

    [[nodiscard]] GameField create(const int block_num, const int background_num,
        const sf::Vector2i &door_size_count = {DOOR_SIZE_COUNT, DOOR_SIZE_COUNT},
        const sf::Vector2f &block_scale = { BLOCK_SCALE, BLOCK_SCALE },
        const sf::Vector2f &background_scale = { BACKGROUND_SCALE, BACKGROUND_SCALE }) const;
    
    ~GameFieldCreator() noexcept = default;
    GameFieldCreator(GameFieldCreator&&) noexcept = delete;
    GameFieldCreator& operator=(GameFieldCreator&&) noexcept = delete;
    GameFieldCreator(const GameFieldCreator&) noexcept = delete;
    GameFieldCreator& operator=(const GameFieldCreator&) noexcept = delete;
};
