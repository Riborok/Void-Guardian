#pragma once

#include <array>
#include <vector>
#include <SFML/Window/Keyboard.hpp>

#include "AdditionalFunc.hpp"
#include "ElementType.hpp"
#include "TypesDef.hpp"

class Executor {
public:
    virtual void handle(const int delta_time) = 0;
    virtual ~Executor() noexcept = default;
    Executor() noexcept = default;
    Executor(Executor&&) noexcept = default;
    Executor& operator=(Executor&&) noexcept = default;
    
    Executor(const Executor&) noexcept = delete;
    Executor& operator=(const Executor&) noexcept = delete;
};

struct Control final {
    sf::Keyboard::Key move;
    sf::Keyboard::Key shoot;
};

struct SimpleSpriteInfo {
    StringVector src;
    int z_index;
    SimpleSpriteInfo(StringVector &&src_, const int z_index_): src(std::move(src_)), z_index(z_index_) {}
};

struct AnimatedSpriteInfo final : SimpleSpriteInfo {
    int frame_count;
    int frame_time;
    AnimatedSpriteInfo(StringVector &&src_, const int frame_count_, const int frame_time_,
        const int z_index_): SimpleSpriteInfo(std::move(src_), z_index_), frame_count(frame_count_), frame_time(frame_time_){}
};

struct RotatedRectangleData final {
    sf::Vector2f p0;
    sf::Vector2f size;
    float angle;
    
    RotatedRectangleData(const sf::Vector2f& p0, const sf::Vector2f& size, const float angle)
        : p0(p0), size(size), angle(angle) { }
};

struct ElementData final {
    sf::Vector2f point;
    float angle;
    ElementTypes type;
    int num;
    sf::Vector2f scale;
    ElementData(const sf::Vector2f& point, const float angle,
                const ElementTypes type, const int num, const sf::Vector2f& scale) :
        point(point), angle(angle), type(type), num(num), scale(scale) { }
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

typedef std::array<SimpleSpriteInfo, static_cast<size_t>(ANIMATED_TYPES_START)> SimpleSpriteInfos;
typedef std::array<AnimatedSpriteInfo, ELEMENT_TYPES_COUNT - static_cast<size_t>(ANIMATED_TYPES_START)> AnimatedSpriteInfos;

struct PlayerInfo final {
    sf::Vector2f scale;
    float speed;
    PlayerInfo(const sf::Vector2f &scale, const float speed): scale(scale), speed(speed){}
};

struct GameData final {
    SimpleSpriteInfos simple_sprite_infos;
    AnimatedSpriteInfos animated_sprite_infos;
    
    BuildingData background_data;
    LocationBuildingData boundary_data;
    
    std::string title;
    std::string icon_src;
    
    sf::Vector2i latest_map_index;
    PlayerInfo player_info;
    
    GameData(const SimpleSpriteInfos& simple_sprite_infos,
            const AnimatedSpriteInfos& animated_sprite_infos,
            const BuildingData& background_data,
            const LocationBuildingData& boundary_data,
            std::string&& game_title,
            std::string&& game_icon_src,
            const PlayerInfo &player_info,
            const sf::Vector2i& latest_map_index) :
        simple_sprite_infos(simple_sprite_infos),
        animated_sprite_infos(animated_sprite_infos),
        background_data(background_data),
        boundary_data(boundary_data),
        title(std::move(game_title)),
        icon_src(std::move(game_icon_src)),
        latest_map_index(latest_map_index),
        player_info(player_info){ }
};