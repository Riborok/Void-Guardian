#pragma once
#include <unordered_set>

#include "../../additionally/Types.h"
#include "../../element/Element.h"
#include "../../sprite/AnimatedSprite.h"
#include "../identifiable/Identifiable.h"
#include "../identifiable/IdTracker.h"

class SpriteStateExecutor final : public Types::Executor {
    std::unordered_set<Element*, IdentifiableHash> *_elements;
    Quadtree *_quadtree;
public:
    SpriteStateExecutor(std::unordered_set<Element*, IdentifiableHash> &elements, Quadtree &quadtree):
        _elements(&elements), _quadtree(&quadtree) {  }
    
    void handle(const int delta_time) override {
        std::vector<Element*> elements_to_delete;
        
        for (auto *element : *_elements) {
            const unsigned int id = element->getId();
            if (IdTracker::isAnimated(id)) {
                auto *animated_sprite = static_cast<AnimatedSprite*>(&element->getSprite()); // NOLINT(cppcoreguidelines-pro-type-static-cast-downcast)
                animated_sprite->changeState(delta_time);
                if (IdTracker::isAnimation(id) && animated_sprite->isAnimationRestarted())
                    elements_to_delete.push_back(element);
            }
        }
        for (auto *element : elements_to_delete) {
            _elements->erase(element);
            _quadtree->remove(element);
            delete element;
        }
    }
    ~SpriteStateExecutor() noexcept override = default;
    
    SpriteStateExecutor(SpriteStateExecutor&&) noexcept = default;
    SpriteStateExecutor& operator=(SpriteStateExecutor&&) noexcept = default;
        
    SpriteStateExecutor(const SpriteStateExecutor&) noexcept = delete;
    SpriteStateExecutor& operator=(const SpriteStateExecutor&) noexcept = delete;
};
