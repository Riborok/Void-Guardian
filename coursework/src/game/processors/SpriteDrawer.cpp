#include "../../../include/game/processors/SpriteDrawer.hpp"

SpriteDrawer::SpriteDrawer(sf::RenderWindow &window, const sf::Color &color): _window(&window), _color(color) { }

void SpriteDrawer::drawFromPq(SpritesPQ &pq) const {
    sf::Sprite sprite;
    while (!pq.empty()) {
        pq.top()->fillSprite(sprite);
        pq.pop();
        _window->draw(sprite);
    }
}

void SpriteDrawer::drawAll(const ElementCollisionSet &elements) const {
    SpritesPQ pq(elements.begin(), elements.end());
    _window->clear(_color);
    drawFromPq(pq);
    _window->display();
}