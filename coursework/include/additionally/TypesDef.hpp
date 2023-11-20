#pragma once
#include <unordered_set>
#include "../element/Element.hpp"

typedef std::unordered_set<const Element*, IdentifiableHash> ElementCollisionSet;

typedef std::vector<std::string> StringVector;

typedef std::pair<sf::Vector2i, sf::Vector2i> MinMaxPoint;