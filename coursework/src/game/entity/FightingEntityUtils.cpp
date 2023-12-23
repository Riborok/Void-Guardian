#include "../../../include/game/entity/FightingEntityUtils.hpp"

sf::Vector2f FightingEntityUtils::calcCenter(const FightingEntity& fighting_entity) {
    return fighting_entity.getCharacter().getElement().getPolygon().calcCenter();
}

void FightingEntityUtils::updateGun(const Gun& gun, const sf::Vector2f& target_p, const float target_a,
        QuadtreeEl& quadtree_el) {
    const auto* element = &gun.getElement();
    
    quadtree_el.remove(element);
    gun.update(target_p, target_a);
    quadtree_el.insert(element);
}

bool FightingEntityUtils::needsMirror(const bool is_mirrored, const bool is_angle_in_quadrant2_or3) {
    return (is_mirrored && !is_angle_in_quadrant2_or3) || (!is_mirrored && is_angle_in_quadrant2_or3);
}