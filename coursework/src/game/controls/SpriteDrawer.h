#pragma once
#include <queue>
#include <unordered_set>
#include <SFML/Graphics/RenderWindow.hpp>

#include "../../element/Element.h"

class SpriteDrawer final {
    sf::RenderWindow *_window;
    sf::Color _color;
    std::priority_queue<SimpleSprite*> _pq;
public:
    SpriteDrawer(sf::RenderWindow &window, const sf::Color &color): _window(&window), _color(color){
    }
    explicit SpriteDrawer(sf::RenderWindow &window): _window(&window), _color(36, 36, 36){
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
        for (const auto element : elements)
            _pq.emplace(&element->getSprite());
    }
    void add(SimpleSprite &z_index_sprite) {
        _pq.emplace(&z_index_sprite);
    }

    ~SpriteDrawer() noexcept = default;
    
    SpriteDrawer(const SpriteDrawer&) noexcept = delete;
    SpriteDrawer& operator=(const SpriteDrawer&) noexcept = delete;
    SpriteDrawer(SpriteDrawer&&) noexcept = delete;
    SpriteDrawer& operator=(SpriteDrawer&&) noexcept = delete;
};
