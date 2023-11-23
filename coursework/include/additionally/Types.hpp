#pragma once

#include <array>
#include <vector>
#include <string>
#include <SFML/Window/Keyboard.hpp>

#include "AdditionalFunc.hpp"
#include "ElementType.hpp"

typedef std::pair<sf::Vector2i, sf::Vector2i> MinMaxPoint;

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

struct SimpleInfo {
    std::string src;
    int z_index;
    SimpleInfo(std::string &&src, const int z_index) : src(std::move(src)), z_index(z_index) {}
    SimpleInfo(const SimpleInfo& info, const int num) :
        src(info.src + std::to_string(num) + ".png"),
        z_index(info.z_index) {}
};
struct AnimationInfo final : SimpleInfo {
    int frame_count;
    int frame_time;
    AnimationInfo(const int count, const int time, std::string &&src_, const int z_index_) :
        SimpleInfo(std::move(src_), z_index_), frame_count(count), frame_time(time) {}
    AnimationInfo(const AnimationInfo& info, const int num):
        SimpleInfo(info, num), frame_count(info.frame_count), frame_time(info.frame_time) {}
};
typedef std::vector<SimpleInfo> SimpleSpriteInfo;
typedef std::vector<AnimationInfo> AnimatedSpriteInfo;

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
    
    PlayerInfo player_info;
    sf::Vector2i latest_map_index;
    
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
        player_info(player_info),
        latest_map_index(latest_map_index) { }
};

struct TransformParams final {
    sf::Vector2f origin;
    sf::Vector2f scale;
    TransformParams(const sf::Vector2f& origin, const sf::Vector2f& scale)
        : origin(origin), scale(scale) {}
};