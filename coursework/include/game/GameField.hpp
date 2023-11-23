#pragma once
#include "../additionally/other types/QuadtreeEl.hpp"
#include "../additionally/other types/QuadtreeLoc.hpp"

struct GameField final {
    GameField(const MinMaxPoint &min_max_point, const sf::Vector2f &start);
    QuadtreeEl quadtree_el;
    QuadtreeLoc quadtree_loc;
    sf::Vector2f start;
};
