#pragma once
#include <queue>
#include <SFML/Graphics/RenderWindow.hpp>

#include "../../sprite/ZIndexSprite.h"

class SpriteDrawer {
    sf::RenderWindow *_window;
    sf::Color _color;
    std::priority_queue<ZIndexSprite*> _pq;
public:
    SpriteDrawer(sf::RenderWindow &window, const sf::Color &color): _window(&window), _color(color){
    }
    explicit SpriteDrawer(sf::RenderWindow &window): _window(&window), _color(36, 36, 36){
    }
    void drawAll() {
        _window->clear(_color);

        while (!_pq.empty()) {
            const ZIndexSprite *sprite = _pq.top();
            _pq.pop();

            _window->draw(*sprite);
        }

        _window->display();
    }
    void add(ZIndexSprite &sprite) {
        _pq.emplace(&sprite);
    }
};
