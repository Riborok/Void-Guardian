#pragma once
#include <vector>

#include "../../element/Element.hpp"
#include "../../quadtree/quadtree type defs/QuadtreeEl.hpp"

class AnimationAttacher final {
    friend AnimationExecutor;
    typedef std::vector<Element*> Animations;
    QuadtreeEl *_quadtree;
    Animations _animations;
public:
    explicit AnimationAttacher(QuadtreeEl &quadtree);
    void addAnimation(Element *animation);
    [[nodiscard]] bool isEmpty() const;

    ~AnimationAttacher() noexcept = default;
    AnimationAttacher(AnimationAttacher&&) noexcept = default;
    AnimationAttacher& operator=(AnimationAttacher&&) noexcept = delete;
    AnimationAttacher(const AnimationAttacher&) noexcept = delete;
    AnimationAttacher& operator=(const AnimationAttacher&) noexcept = delete;
};