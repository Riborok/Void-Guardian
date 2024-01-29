#pragma once

#include "Executor.hpp"
#include "../element subtype handlers/AnimationAttacher.hpp"

class AnimationExecutor final : public Executor {
    QuadtreeEl *_quadtree;
    AnimationAttacher::Animations *_animations;
public:
    AnimationExecutor(QuadtreeEl &quadtree, AnimationAttacher &animation_attacher);
    void handle(const int delta_time) override;
    
    ~AnimationExecutor() noexcept override = default;
    AnimationExecutor(AnimationExecutor&&) noexcept = default;
    AnimationExecutor& operator=(AnimationExecutor&&) noexcept = delete;
    AnimationExecutor(const AnimationExecutor&) noexcept = delete;
    AnimationExecutor& operator=(const AnimationExecutor&) noexcept = delete;
};
