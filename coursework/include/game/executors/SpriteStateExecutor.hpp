#pragma once
#include <unordered_set>

#include "../../additionally/Types.hpp"
#include "../../element/Element.hpp"
#include "../../Quadtree/Quadtree.hpp"
#include "../identifiable/Identifiable.hpp"

class SpriteStateExecutor final : public Types::Executor {
    std::unordered_set<Element*, IdentifiableHash> *_elements;
    Quadtree<Element> *_quadtree;
public:
    SpriteStateExecutor(std::unordered_set<Element*, IdentifiableHash>& elements, Quadtree<Element>& quadtree);

    void handle(const int delta_time) override;
    
    ~SpriteStateExecutor() noexcept override = default;
    
    SpriteStateExecutor(SpriteStateExecutor&&) noexcept = default;
    SpriteStateExecutor& operator=(SpriteStateExecutor&&) noexcept = default;
        
    SpriteStateExecutor(const SpriteStateExecutor&) noexcept = delete;
    SpriteStateExecutor& operator=(const SpriteStateExecutor&) noexcept = delete;
};
