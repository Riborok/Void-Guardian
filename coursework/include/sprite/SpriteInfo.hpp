#pragma once
#include <array>
#include <vector>
#include <string>

#include "../element/ElementType.hpp"

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

class SimpleSpriteInfos final {
    static constexpr size_t COUNT = static_cast<size_t>(ANIMATED_TYPES_START);
    typedef std::initializer_list<std::pair<const ElementType, SimpleSpriteInfo&&>> InitList;
    typedef std::array<SimpleSpriteInfo, COUNT> Infos;
    
    Infos _arr;
public:
    SimpleSpriteInfos(const InitList &pairs);

    const SimpleSpriteInfo& operator[](const ElementType index) const;

    ~SimpleSpriteInfos() noexcept = default;
    SimpleSpriteInfos(SimpleSpriteInfos&&) noexcept = default;
    SimpleSpriteInfos& operator=(SimpleSpriteInfos&&) noexcept = delete;
    SimpleSpriteInfos(const SimpleSpriteInfos&) noexcept = delete;
    SimpleSpriteInfos& operator=(const SimpleSpriteInfos&) noexcept = delete;
};

class AnimatedSpriteInfos final {
    static constexpr size_t START_INDEX = static_cast<size_t>(ANIMATED_TYPES_START);
    static constexpr size_t COUNT = ELEMENT_TYPES_COUNT - START_INDEX;
    typedef std::initializer_list<std::pair<const ElementType, AnimatedSpriteInfo&&>> InitList;
    typedef std::array<AnimatedSpriteInfo, COUNT> Infos;
    
    Infos _arr;
public:
    AnimatedSpriteInfos(const InitList &pairs);

    const AnimatedSpriteInfo& operator[](const ElementType index) const;

    ~AnimatedSpriteInfos() noexcept = default;
    AnimatedSpriteInfos(AnimatedSpriteInfos&&) noexcept = default;
    AnimatedSpriteInfos& operator=(AnimatedSpriteInfos&&) noexcept = delete;
    AnimatedSpriteInfos(const AnimatedSpriteInfos&) noexcept = delete;
    AnimatedSpriteInfos& operator=(const AnimatedSpriteInfos&) noexcept = delete;
};