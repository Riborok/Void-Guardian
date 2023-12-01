#include "../../../include/game/executors/AnimationExecutor.hpp"

#include <cassert>
#include "../../../include/game/identifiable/ElementIdTracker.hpp"
#include "../../../include/sprite/AnimatedSprite.hpp"

AnimationExecutor::AnimationExecutor(QuadtreeEl &quadtree): _quadtree(&quadtree) { }

void AnimationExecutor::addAnimation(Element *animation) {
    assert(ElementIdTracker::isAnimation(animation->getId()));
    _animations.push_back(animation);
    _quadtree->insert(animation);
}

void AnimationExecutor::handle(const int delta_time) {
    for (auto it = _animations.begin(); it != _animations.end();) {
        const auto* animation = *it;
        auto* animated_sprite = static_cast<AnimatedSprite*>(animation->_sprite); // NOLINT(cppcoreguidelines-pro-type-static-cast-downcast)
        animated_sprite->changeState(delta_time);

        if (animated_sprite->isAnimationRestarted()) {
            it = _animations.erase(it);
            _quadtree->remove(animation);
            delete animation;
        }
        else
            ++it;
    }
}