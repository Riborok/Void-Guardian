#pragma once
#include "../element/Element.hpp"
#include "../game/construction/Location.hpp"
#include "../Quadtree/Quadtree.hpp"

typedef Quadtree<Element> QuadtreeEl;
typedef Quadtree<Location> QuadtreeLoc;

typedef std::unordered_set<const Element*, IdentifiableHash> ElementCollisionSet;

typedef std::vector<std::string> StringVector;

typedef std::pair<sf::Vector2i, sf::Vector2i> MinMaxPoint;