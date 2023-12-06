#pragma once
#include "CollisionResult.hpp"
#include "../../element/Element.hpp"

namespace CollisionResolution {
    void separateElement(const Element& element, const CollisionResult &collision_result);
    void separateElement(const Element& element, const sf::Vector2f &collision_normal, const float overlap);
}