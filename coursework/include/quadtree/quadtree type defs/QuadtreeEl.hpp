#pragma once
#include "../Quadtree.hpp"
#include "../../element/Element.hpp"

constexpr size_t QUADTREE_EL_CAPACITY = 10;
typedef Quadtree<const Element> QuadtreeEl;