#pragma once
#include <SFML/System/Vector2.hpp>

#include "PlayerInfo.hpp"
#include "SpriteInfo.hpp"
#include "../AdditionalFunc.hpp"
#include "../../geometry/collision/CollisionTable.hpp"

struct BuildingData {
    int num;
    sf::Vector2i size;
    sf::Vector2f scale;
    sf::Vector2i delta;
    BuildingData(const int num, const sf::Vector2i& size,
        const sf::Vector2f& scale) :
            num(num), size(size), scale(scale),
            delta(AdditionalFunc::getScaledSize(size, scale)) { }
};

struct LocationBuildingData final : BuildingData {
    sf::Vector2i door_size_count;
    LocationBuildingData(const int num_, const sf::Vector2i& size_,
        const sf::Vector2f& scale_, const sf::Vector2i& door_size_count) :
            BuildingData(num_, size_, scale_), door_size_count(door_size_count){ }
};

struct ElementData final {
    sf::Vector2f point;
    float angle;
    ElementType type;
    int num;
    sf::Vector2f scale;
    ElementData(const sf::Vector2f& point, const float angle,
                const ElementType type, const int num, const sf::Vector2f& scale) :
        point(point), angle(angle), type(type), num(num), scale(scale) { }
};

struct RotatedRectangleData final {
    sf::Vector2f p0;
    sf::Vector2f size;
    float angle;
    RotatedRectangleData(const sf::Vector2f& p0, const sf::Vector2f& size, const float angle)
        : p0(p0), size(size), angle(angle) { }
};

struct AlignedRectangleData final {
    float x0;
    float y0;
    float x1;
    float y1;
    AlignedRectangleData(const float x0, const float y0, const float x1, const float y1) :
        x0(x0), y0(y0), x1(x1), y1(y1) { }
    explicit AlignedRectangleData(const MinMaxPoint &min_max_point) :
        x0(static_cast<float>(min_max_point.first.x)), y0(static_cast<float>(min_max_point.first.y)),
        x1(static_cast<float>(min_max_point.second.x)), y1(static_cast<float>(min_max_point.second.y)) { }
};

struct GameData final {
    SimpleSpriteInfos simple_sprite_infos;
    AnimatedSpriteInfos animated_sprite_infos;
    CollisionTable collision_table;
    
    BuildingData background_data;
    LocationBuildingData boundary_data;
    sf::Vector2i latest_map_index;
    
    std::string title;
    std::string icon_src;
    
    PlayerInfo player_info;
    
    GameData(SimpleSpriteInfos&& simple_sprite_infos,
            AnimatedSpriteInfos&& animated_sprite_infos,
            CollisionTable &&collision_table,
            const BuildingData& background_data,
            const LocationBuildingData& boundary_data,
            const sf::Vector2i& latest_map_index,
            std::string&& game_title,
            std::string&& game_icon_src,
            const PlayerInfo &player_info) :
        simple_sprite_infos(std::move(simple_sprite_infos)),
        animated_sprite_infos(std::move(animated_sprite_infos)),
        collision_table(std::move(collision_table)),
        background_data(background_data),
        boundary_data(boundary_data),
        latest_map_index(latest_map_index),
        title(std::move(game_title)),
        icon_src(std::move(game_icon_src)),
        player_info(player_info){ }
};