#pragma once
#include <unordered_set>

#include "../../additionally/Types.h"
#include "../../element/Element.h"
#include "../../sprite/AnimatedSprite.h"
#include "../identifiable/Identifiable.h"
#include "../identifiable/IdTracker.h"

class SpriteStateExecutor final : public Types::Executor {
    std::unordered_set<Element*, IdentifiableHash> *_elements = nullptr;
public:
    void handle(const int delta_time) override {
        if (_elements) {
            for (const auto *element : *_elements)
                if (IdTracker::isAnimated(element->getId()))
                    static_cast<AnimatedSprite*>(&element->getSprite())->changeState(delta_time); // NOLINT(cppcoreguidelines-pro-type-static-cast-downcast)
            _elements = nullptr;
        }
    }
    void setElements(std::unordered_set<Element*, IdentifiableHash> *elements) { _elements = elements; }

    ~SpriteStateExecutor() noexcept override = default;
    SpriteStateExecutor() noexcept = default;
    
    SpriteStateExecutor(SpriteStateExecutor&&) noexcept = default;
    SpriteStateExecutor& operator=(SpriteStateExecutor&&) noexcept = default;
        
    SpriteStateExecutor(const SpriteStateExecutor&) noexcept = delete;
    SpriteStateExecutor& operator=(const SpriteStateExecutor&) noexcept = delete;
};
