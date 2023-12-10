#pragma once
#include "../../element/ElementCreator.hpp"
#include "bullet/Bullet.hpp"
#include "player/Player.hpp"

class DyingEffectAnimator final {
    static constexpr float SCALE_FACTOR = -0.0175f;
    static const sf::Vector2f OFFSET_FACTOR;
    
    ElementCreator *_element_creator;
    AnimationExecutor *_animation_executor;
    mutable std::uniform_int_distribution<int> _num{0, 4};
public:
    DyingEffectAnimator(ElementCreator& element_creator, AnimationExecutor& animation_executor);
    void createAnimation(const Player &player) const;
    void createAnimation(const Bullet &bullet, const Polygon &murder_polygon) const;

    ~DyingEffectAnimator() noexcept = default;
    DyingEffectAnimator(DyingEffectAnimator&&) noexcept = default;
    DyingEffectAnimator& operator=(DyingEffectAnimator&&) noexcept = default;
    DyingEffectAnimator(const DyingEffectAnimator&) noexcept = delete;
    DyingEffectAnimator& operator=(const DyingEffectAnimator&) noexcept = delete;
};
