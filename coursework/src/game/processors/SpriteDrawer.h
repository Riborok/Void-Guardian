#pragma once
#include <queue>
#include <unordered_set>
#include <SFML/Graphics/RenderWindow.hpp>

#include "../../element/Element.h"

class SpriteDrawer final {
    static constexpr sf::Uint8 DEFAULT_COLOR_VALUE = 36;

    std::priority_queue<SimpleSprite*, std::vector<SimpleSprite*>, SimpleSpriteCompare> _pq;
    sf::RenderWindow *_window;
    std::unordered_set<Element*, IdentifiableHash> *_elements;
    sf::Color _color;

    void addToPq() {
        for (const auto *element : *_elements)
            _pq.push(&element->getSprite());      
    }
    void drawFromPq() {
        while (!_pq.empty()) {
            _window->draw(*_pq.top());
            _pq.pop();
        }
    }
public:
    SpriteDrawer(sf::RenderWindow &window, std::unordered_set<Element*, IdentifiableHash> &elements,
            const sf::Color &color = {DEFAULT_COLOR_VALUE, DEFAULT_COLOR_VALUE, DEFAULT_COLOR_VALUE}):
        _window(&window), _elements(&elements), _color(color) { }
    
    void drawAll() {
        addToPq();
        _window->clear(_color);
        drawFromPq();
        _window->display();
    }

    ~SpriteDrawer() noexcept = default;
    
    SpriteDrawer(const SpriteDrawer&) noexcept = delete;
    SpriteDrawer& operator=(const SpriteDrawer&) noexcept = delete;
    SpriteDrawer(SpriteDrawer&&) noexcept = delete;
    SpriteDrawer& operator=(SpriteDrawer&&) noexcept = delete;
};