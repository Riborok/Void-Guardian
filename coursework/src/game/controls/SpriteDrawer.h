#pragma once
#include <queue>
#include <unordered_set>
#include <SFML/Graphics/RenderWindow.hpp>

#include "../../element/Element.h"

class SpriteDrawer final {
    sf::RenderWindow *_window;
    sf::Color _color;
    std::priority_queue<SimpleSprite*, std::vector<SimpleSprite*>, SimpleSpriteCompare> _pq;
    std::vector<AnimatedSprite*> _animated_sprites;
public:
    SpriteDrawer(sf::RenderWindow &window, const sf::Color &color): _window(&window), _color(color){
    }
    explicit SpriteDrawer(sf::RenderWindow &window): _window(&window), _color(36, 36, 36){
    }
    void drawAll(const int delta_time) {
        for (auto *animated_sprite : _animated_sprites)
            animated_sprite->changeState(delta_time);
        _animated_sprites.clear();
        
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
        auto *sprite = &element->getSprite();
        _pq.push(sprite);
        if (IdTracker::isAnimated(element->getId()))
            _animated_sprites.push_back(static_cast<AnimatedSprite*>(sprite));  // NOLINT(cppcoreguidelines-pro-type-static-cast-downcast)
    }

    ~SpriteDrawer() noexcept = default;
    
    SpriteDrawer(const SpriteDrawer&) noexcept = delete;
    SpriteDrawer& operator=(const SpriteDrawer&) noexcept = delete;
    SpriteDrawer(SpriteDrawer&&) noexcept = delete;
    SpriteDrawer& operator=(SpriteDrawer&&) noexcept = delete;
};