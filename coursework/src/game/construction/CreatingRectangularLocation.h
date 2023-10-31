#pragma once
#include <SFML/System/Vector2.hpp>

#include "../../element/ElementCreation.h"
#include "../../Quadtree/Quadtree.h"

namespace CreatingRectangularLocation {
    inline sf::Vector2f createBackground(const int num, const sf::Vector2f &p0, const sf::Vector2f &p1, Quadtree &quadtree, const float scale) {
        const float dx = Constants::BACKGROUND_SIZE.x * scale, dy = Constants::BACKGROUND_SIZE.y * scale;
        
        sf::Vector2f p(p0);
        
        while (p.y < p1.y) {
            p.x = p0.x;
            while (p.x < p1.x) {
                quadtree.insert(ElementCreation::create(p, 0, Types::ElementTypes::BACKGROUND, num, scale));
                p.x += dx;
            }
            p.y += dy;
        }
        
        return p;
    }
}
