#pragma once
#include "../Quadtree/QuadtreeTypeDefs/QuadtreeEl.hpp"
#include "../Quadtree/QuadtreeTypeDefs/QuadtreeLoc.hpp"

struct GameField final {
    QuadtreeEl quadtree_el;
    QuadtreeLoc quadtree_loc;
    sf::Vector2f start;
    GameField(const MinMaxPoint &min_max_point, const sf::Vector2f &start);
};
