#pragma once
#include "../additionally/TypesDef.hpp"

struct GameField final {
    GameField(const MinMaxPoint &min_max_point, const sf::Vector2f &start);
    QuadtreeEl quadtree_el;
    QuadtreeLoc quadtree_loc;
    sf::Vector2f start;
};
