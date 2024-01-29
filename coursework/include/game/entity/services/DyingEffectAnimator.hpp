#pragma once
#include "../../../element/ElementCreator.hpp"
#include "../../element subtype handlers/AnimationAttacher.hpp"
#include "../bullet/Bullet.hpp"
#include "../player/Player.hpp"

class DyingEffectAnimator final {
    static constexpr float SCALE_FACTOR = -0.0175f;
    const sf::Vector2f _offset_factor{-1.0f, -0.5f};
    
    ElementCreator *_element_creator;
    AnimationAttacher *_animation_attacher;
    mutable std::uniform_int_distribution<size_t> _num{0, 4};
public:
    DyingEffectAnimator(ElementCreator& element_creator, AnimationAttacher &animation_attacher);
    void createAnimation(const Bullet &bullet, const Polygon &murder_polygon) const;
    void createAnimation(const FightingEntity &entity) const;

    ~DyingEffectAnimator() noexcept = default;
    DyingEffectAnimator(DyingEffectAnimator&&) noexcept = default;
    DyingEffectAnimator& operator=(DyingEffectAnimator&&) noexcept = delete;
    DyingEffectAnimator(const DyingEffectAnimator&) noexcept = delete;
    DyingEffectAnimator& operator=(const DyingEffectAnimator&) noexcept = delete;
};
