#include "../../../include/game/processors/GameUpdater.hpp"

#include "../../../include/model/polygon/Rectangle.hpp"

GameUpdater::GameUpdater(const Polygon &focus, sf::RenderWindow &window, QuadtreeEl &quadtree) :
    _focus(&focus), _window(&window), _quadtree(&quadtree),
    _window_param(static_cast<sf::Vector2f>(window.getSize())) { }

void GameUpdater::updateView() {
    _window_param.setFocus(_focus->calcCenter());
    _window->setView(_window_param.getView());
}

void GameUpdater::fillCollisionSet(ElementCollisionSet &element_collision_set) const {
    const Rectangle rect(_focus->calcCenter(), _window_param.getWindowHalfSize());
    _quadtree->getCollisions(rect, element_collision_set);
}

WindowParam& GameUpdater::getWindowParam() { return _window_param; }