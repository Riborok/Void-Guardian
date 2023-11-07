#include "../../../include/game/executors/SpriteStateExecutor.hpp"

#include "../../../include/game/identifiable/IdTracker.hpp"
#include "../../../include/sprite/AnimatedSprite.hpp"

SpriteStateExecutor::SpriteStateExecutor(std::unordered_set<Element*, IdentifiableHash>& elements, Quadtree<Element>& quadtree)
    : _elements(&elements), _quadtree(&quadtree) {}

void SpriteStateExecutor::handle(const int delta_time) {
    std::vector<Element*> elements_to_delete;

    for (auto* element : *_elements) {
        if (const size_t id = element->getId(); IdTracker::isAnimated(id)) {
            auto* animated_sprite = static_cast<AnimatedSprite*>(&element->getSprite()); // NOLINT(cppcoreguidelines-pro-type-static-cast-downcast)
            animated_sprite->changeState(delta_time);
            if (IdTracker::isAnimation(id) && animated_sprite->isAnimationRestarted())
                elements_to_delete.push_back(element);
        }
    }
    for (auto* element : elements_to_delete) {
        _elements->erase(element);
        _quadtree->remove(element);
        delete element;
    }
}