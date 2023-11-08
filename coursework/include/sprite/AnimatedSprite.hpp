#pragma once
#include "SimpleSprite.hpp"

class AnimatedSprite final : public SimpleSprite {
    int _frame_count;
    int _frame_time;
    int _frame_width;
    sf::IntRect _texture_rect;
    int _elapsed_time = 0;

public:
    AnimatedSprite(const std::string &src, const int frame_count, const int frame_time, const int z_index);

    void changeState(const int delta_time);
    bool isAnimationRestarted() const;

    ~AnimatedSprite() noexcept override = default;

    AnimatedSprite(const AnimatedSprite&) noexcept = delete;
    AnimatedSprite& operator=(const AnimatedSprite&) noexcept = delete;
    AnimatedSprite(AnimatedSprite&&) noexcept = delete;
    AnimatedSprite& operator=(AnimatedSprite&&) noexcept = delete;
};