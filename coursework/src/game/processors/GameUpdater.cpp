#include "../../../include/game/processors/GameUpdater.hpp"

#include "../../../include/additionally/TypesDef.hpp"
#include "../../../include/model/polygon/Rectangle.hpp"

GameUpdater::GameUpdater(const Polygon &focus, sf::RenderWindow &window, QuadtreeEl &quadtree) :
    _focus(&focus), _window(&window), _quadtree(&quadtree),
    _window_param(static_cast<sf::Vector2f>(window.getSize())) { }

void GameUpdater::setParameters(const sf::Vector2f &focus) {
    _elements.clear();
    const Rectangle rect(focus, _window_param.getWindowHalfSize());
    _quadtree->getCollisions(rect, _elements);
}

void GameUpdater::updateView(const sf::Vector2f &focus) {
    _window_param.setFocus(focus);
    _window->setView(_window_param.getView());
}

void GameUpdater::update() {
    const auto focus(_focus->calcCenter());
    setParameters(focus);
    updateView(focus);
}

const ElementCollisionSet& GameUpdater::getElements() const { return _elements; }

WindowParam& GameUpdater::getWindowParam() { return _window_param; }

void GameUpdater::removeElement(const Element* element) {
    _elements.erase(element);
    _quadtree->remove(element);
    delete element;
}