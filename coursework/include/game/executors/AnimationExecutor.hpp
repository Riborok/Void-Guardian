#pragma once

#include "Executor.hpp"
#include "../managers/AnimationManager.hpp"

class AnimationExecutor final : public Executor {
    QuadtreeEl *_quadtree;
    AnimationManager::Animations *_animations;
public:
    AnimationExecutor(QuadtreeEl &quadtree, AnimationManager &animation_manager);
    void handle(const int delta_time) override;
    
    ~AnimationExecutor() noexcept override = default;
    AnimationExecutor(AnimationExecutor&&) noexcept = default;
    AnimationExecutor& operator=(AnimationExecutor&&) noexcept = delete;
    AnimationExecutor(const AnimationExecutor&) noexcept = delete;
    AnimationExecutor& operator=(const AnimationExecutor&) noexcept = delete;
};
