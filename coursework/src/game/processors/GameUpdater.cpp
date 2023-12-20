﻿#include "../../../include/game/processors/GameUpdater.hpp"

#include "../../../include/model/rectangle/Rectangle.hpp"

const sf::Vector2f& GameUpdater::getFocus() {
    if (!_player_map->getMap().empty())
        _prev_focus = _player_map->getMap().begin()->second->getCharacter().getElement().getPolygon().calcCenter();
    return _prev_focus;
}

GameUpdater::GameUpdater(PlayerMap &player_map, sf::RenderWindow &window, QuadtreeEl &quadtree) :
    _player_map(&player_map), _window(&window), _quadtree(&quadtree),
    _window_param(static_cast<sf::Vector2f>(window.getSize())) { }

void GameUpdater::updateView() {
    _window_param.setFocus(getFocus());
    _window->setView(_window_param.getView());
}

void GameUpdater::fillCollisionSet(ElementCollisionSet &element_collision_set) {
    const Rectangle rect(getFocus(), _window_param.getWindowHalfSize());
    _quadtree->fillCollisionSet(rect, element_collision_set);
}

WindowParam& GameUpdater::getWindowParam() { return _window_param; }