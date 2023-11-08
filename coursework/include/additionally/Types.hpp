#pragma once

#include <vector>
#include <SFML/Window/Keyboard.hpp>

#include "TypesDef.hpp"

constexpr size_t AMOUNT_OF_ELEMENT_TYPES = 5;
enum class ElementTypes final : size_t {
    // Simple
    BACKGROUND = 0,
    BLOCK,
    GUN,

    // Animated
    WRAITH,

    // Animation
    WRAITH_DYING
};
constexpr ElementTypes ANIMATED_TYPES_START = ElementTypes::WRAITH;
constexpr ElementTypes ANIMATION_TYPES_START = ElementTypes::WRAITH_DYING;
constexpr size_t AMOUNT_OF_OTHERS_TYPES = 1;
constexpr size_t LOCATION = AMOUNT_OF_ELEMENT_TYPES;

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