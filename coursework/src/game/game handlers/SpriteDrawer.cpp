#include "../../../include/game/game handlers/SpriteDrawer.hpp"

SpriteDrawer::SpriteDrawer(sf::RenderWindow &window, FightingInfoDrawer &&fighting_info_drawer, const sf::Color &color):
    _window(&window), _fighting_info_drawer(std::move(fighting_info_drawer)), _color(color) { }

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
    _fighting_info_drawer.drawHealthBars(elements);
    _window->display();
}