#include "../../../include/game/element subtype handlers/AnimationAttacher.hpp"
#include "../../../include/game/identifiable/ElementIdTracker.hpp"
#include <cassert>

AnimationAttacher::AnimationAttacher(QuadtreeEl& quadtree): _quadtree(&quadtree) { }

void AnimationAttacher::addAnimation(Element* animation) {
    assert(ElementIdTracker::isAnimation(animation->getId()));
    _animations.push_back(animation);
    _quadtree->insert(animation);
}

bool AnimationAttacher::isEmpty() const { return _animations.empty(); }