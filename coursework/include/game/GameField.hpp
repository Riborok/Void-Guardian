#pragma once
#include "../quadtree/quadtree type defs/QuadtreeEl.hpp"
#include "../quadtree/quadtree type defs/QuadtreeLoc.hpp"
#include "entity/player/gun/GunManager.hpp"

struct GameField final {
    QuadtreeEl quadtree_el;
    QuadtreeLoc quadtree_loc;
    GunManager gun_manager;
    sf::Vector2f start;
    GameField(const MinMaxPoint &min_max_point, const EntityCreator &entity_creator, const sf::Vector2f &start);
};