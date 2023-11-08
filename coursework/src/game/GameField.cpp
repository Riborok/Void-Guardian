#include "../../include/game/GameField.hpp"

GameField::GameField(const MinMaxPoint &min_max_point, const sf::Vector2f &start) :
    quadtree_el(static_cast<float>(min_max_point.first.x),
                  static_cast<float>(min_max_point.first.y),
                  static_cast<float>(min_max_point.second.x),
                  static_cast<float>(min_max_point.second.y)),
    quadtree_loc(static_cast<float>(min_max_point.first.x),
                   static_cast<float>(min_max_point.first.y),
                   static_cast<float>(min_max_point.second.x),
                   static_cast<float>(min_max_point.second.y)),
    start(start)
{ }