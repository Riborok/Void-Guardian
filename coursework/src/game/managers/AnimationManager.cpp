#include "../../../include/game/managers/AnimationManager.hpp"
#include "../../../include/game/identifiable/ElementIdTracker.hpp"
#include <cassert>

AnimationManager::AnimationManager(QuadtreeEl& quadtree): _quadtree(&quadtree) { }

void AnimationManager::addAnimation(Element* animation) {
    assert(ElementIdTracker::isAnimation(animation->getId()));
    _animations.push_back(animation);
    _quadtree->insert(animation);
}

bool AnimationManager::isEmpty() const { return _animations.empty(); }