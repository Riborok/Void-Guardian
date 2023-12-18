#pragma once
#include "../quadtree/quadtree type defs/QuadtreeEl.hpp"
#include "../quadtree/quadtree type defs/QuadtreeLoc.hpp"
#include "construction/game field creation/arena/enemy spawn/SpawnMap.hpp"

struct GameField final {
    QuadtreeEl quadtree_el;
    QuadtreeLoc quadtree_loc;
    SpawnMap spawn_map;
    sf::Vector2f start;
    GameField(const MinMaxPoint &min_max_point, const sf::Vector2f &start);
}; 