#include "../../../include/geometry/collision/CollisionResolution.hpp"

#include "../../../include/geometry/GeomAuxiliaryFunc.hpp"

sf::Vector2f calcCollisionNormal(const sf::Vector2f& collision_point, const sf::Vector2f& center) {
    sf::Vector2f result(collision_point - center);
    GeomAuxiliaryFunc::normalize(result);
    return result;
}

void CollisionResolution::separateElement(const Element& element, const CollisionResult &collision_result) {
    const sf::Vector2f collision_normal(calcCollisionNormal(collision_result.collision_point, element.getPolygon().calcCenter()));
    const sf::Vector2f correction(collision_normal * -collision_result.overlap);
    element.move(correction);
}
