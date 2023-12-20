#pragma once
#include <vector>

#include "../../element/Element.hpp"
#include "../../quadtree/quadtree type defs/QuadtreeEl.hpp"

class AnimationManager final {
    friend AnimationExecutor;
    typedef std::vector<Element*> Animations;
    QuadtreeEl *_quadtree;
    Animations _animations;
public:
    explicit AnimationManager(QuadtreeEl &quadtree);
    void addAnimation(Element *animation);
    [[nodiscard]] bool isEmpty() const;

    ~AnimationManager() noexcept = default;
    AnimationManager(AnimationManager&&) noexcept = default;
    AnimationManager& operator=(AnimationManager&&) noexcept = delete;
    AnimationManager(const AnimationManager&) noexcept = delete;
    AnimationManager& operator=(const AnimationManager&) noexcept = delete;
};