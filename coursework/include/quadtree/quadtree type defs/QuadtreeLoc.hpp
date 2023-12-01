#pragma once
#include "../../game/construction/Location.hpp"
#include "../Quadtree.hpp"

constexpr size_t QUADTREE_LOC_CAPACITY = 4;
typedef Quadtree<Location> QuadtreeLoc;
