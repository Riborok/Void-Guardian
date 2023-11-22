#include "../../include/game/GameField.hpp"

GameField::GameField(const MinMaxPoint &min_max_point, const sf::Vector2f &start) :
    quadtree_el(AlignedRectangleData{min_max_point}),
    quadtree_loc(AlignedRectangleData{min_max_point}),
    start(start)
{ }