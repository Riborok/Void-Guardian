#pragma once
#include <queue>
#include <unordered_set>
#include <SFML/Graphics/RenderWindow.hpp>

#include "../../element/Element.h"

class SpriteDrawer final {
    enum { DEFAULT_COLOR_VALUE = 36 };
    
    sf::RenderWindow *_window;
    sf::Color _color;
    std::priority_queue<SimpleSprite*, std::vector<SimpleSprite*>, SimpleSpriteCompare> _pq;
public:
    SpriteDrawer(sf::RenderWindow &window, const sf::Color &color): _window(&window), _color(color){
    }
    explicit SpriteDrawer(sf::RenderWindow &window): _window(&window), _color(DEFAULT_COLOR_VALUE, DEFAULT_COLOR_VALUE, DEFAULT_COLOR_VALUE){
    }
    void drawAll() {
        _window->clear(_color);

        while (!_pq.empty()) {
            _window->draw(*_pq.top());
            _pq.pop();
        }

        _window->display();
    }
    void add(const std::unordered_set<Element*, IdentifiableHash> &elements) {
        for (const auto *element : elements)
            add(element);
    }
    void add(const Element *element) {
        _pq.push(&element->getSprite());
    }

    ~SpriteDrawer() noexcept = default;
    
    SpriteDrawer(const SpriteDrawer&) noexcept = delete;
    SpriteDrawer& operator=(const SpriteDrawer&) noexcept = delete;
    SpriteDrawer(SpriteDrawer&&) noexcept = delete;
    SpriteDrawer& operator=(SpriteDrawer&&) noexcept = delete;
};