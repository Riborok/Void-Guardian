#include "../../../include/game/processors/SpriteDrawer.hpp"

SpriteDrawer::SpriteDrawer(sf::RenderWindow &window, const ElementCollisionSet &elements,
                           const sf::Color &color)
    : _window(&window), _elements(&elements), _color(color) { }

void SpriteDrawer::addToPq() {
    for (const auto *element : *_elements)
        _pq.push(element);      
}

void SpriteDrawer::drawFromPq() {
    while (!_pq.empty()) {
        _pq.top()->fillSprite(_sprite);
        _pq.pop();
        _window->draw(_sprite);
    }
}

void SpriteDrawer::drawAll() {
    addToPq();
    _window->clear(_color);
    drawFromPq();
    _window->display();
}