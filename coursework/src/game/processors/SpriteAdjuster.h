﻿#pragma once
#include <unordered_set>

#include "../../element/Element.h"

class SpriteAdjuster final {
    std::unordered_set<Element*, IdentifiableHash> *_elements;
    sf::Vector2f *_offset;
public:
    SpriteAdjuster(std::unordered_set<Element*, IdentifiableHash> &elements, sf::Vector2f &offset) :
        _elements(&elements), _offset(&offset) { }
    
    void adjustPositions() const {
        for (const auto *element : *_elements)
            element->adjustSpritePosition(*_offset);
    }

    ~SpriteAdjuster() noexcept = default;
    
    SpriteAdjuster(const SpriteAdjuster&) = delete;
    SpriteAdjuster& operator=(const SpriteAdjuster&) = delete;
    SpriteAdjuster(SpriteAdjuster&&) = delete;
    SpriteAdjuster& operator=(SpriteAdjuster&&) = delete;
};
