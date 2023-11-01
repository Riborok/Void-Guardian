#pragma once
#include <unordered_set>
#include <SFML/Graphics/RenderWindow.hpp>

#include "../../element/Element.h"

class SpriteAdjuster final {
    sf::RenderWindow *_window;
    std::unordered_set<Element*, IdentifiableHash> *_elements;
public:
    SpriteAdjuster(sf::RenderWindow &window, std::unordered_set<Element*, IdentifiableHash> &elements) :
        _window(&window), _elements(&elements) { }
    void adjustPositions() const {
        const auto size = _window->getSize();
        for (const auto *element : *_elements)
            element->adjustSpritePosition(size);
    }

    ~SpriteAdjuster() noexcept = default;
    
    SpriteAdjuster(const SpriteAdjuster&) = delete;
    SpriteAdjuster& operator=(const SpriteAdjuster&) = delete;
    SpriteAdjuster(SpriteAdjuster&&) = delete;
    SpriteAdjuster& operator=(SpriteAdjuster&&) = delete;
};
