#pragma once

#include "Executor.hpp"
#include "../processors/GameUpdater.hpp"

class AnimationExecutor final : public Executor {
    typedef std::vector<Element*> Animations;

    QuadtreeEl *_quadtree;
    Animations _animations;
public:
    explicit AnimationExecutor(QuadtreeEl &quadtree);
    
    void addAnimation(Element *animation);

    void handle(const int delta_time) override;
    
    ~AnimationExecutor() noexcept override = default;
    AnimationExecutor(AnimationExecutor&&) noexcept = default;
    AnimationExecutor& operator=(AnimationExecutor&&) noexcept = delete;
    AnimationExecutor(const AnimationExecutor&) noexcept = delete;
    AnimationExecutor& operator=(const AnimationExecutor&) noexcept = delete;
};
