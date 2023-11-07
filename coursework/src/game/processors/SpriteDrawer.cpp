#include "../../../include/game/processors/SpriteDrawer.hpp"

SpriteDrawer::SpriteDrawer(sf::RenderWindow &window, std::unordered_set<Element*, IdentifiableHash> &elements,
        const sf::Color &color)
    : _window(&window), _elements(&elements), _color(color) { }

void SpriteDrawer::addToPq() {
    for (const auto *element : *_elements)
        _pq.push(&element->getSprite());      
}

void SpriteDrawer::drawFromPq() {
    while (!_pq.empty()) {
        _window->draw(*_pq.top());
        _pq.pop();
    }
}

void SpriteDrawer::drawAll() {
    addToPq();
    _window->clear(_color);
    drawFromPq();
    _window->display();
}