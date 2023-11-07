#pragma once
#include <SFML/System/Vector2.hpp>

#include "Location.hpp"
#include "../../element/ElementCreation.hpp"
#include "../../Quadtree/Quadtree.hpp"

namespace BoundaryCreation {

    void createHorBoundary(const int num, const sf::Vector2u &p, const unsigned last, Quadtree<Element> &quadtree,
                                  Location *location, const sf::Vector2f &scale,
                                  const unsigned delta, const unsigned offset);

    
    void createVertBoundary(const int num, const sf::Vector2u &p, const unsigned last, Quadtree<Element> &quadtree,
                                   Location *location, const sf::Vector2f &scale,
                                   const unsigned delta, const unsigned offset);
}
