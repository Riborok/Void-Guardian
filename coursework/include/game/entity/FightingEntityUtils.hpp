#pragma once
#include <SFML/System/Vector2.hpp>

#include "FightingEntity.hpp"
#include "../../quadtree/quadtree type defs/QuadtreeEl.hpp"
#include "bullet/BulletCreator.hpp"

namespace FightingEntityUtils {
    sf::Vector2f calcCenter(const FightingEntity &fighting_entity);
    void updateGun(const Gun &gun, const sf::Vector2f &target_p, const float target_a, QuadtreeEl &quadtree_el);
    bool needsMirror(const bool is_mirrored, const bool is_angle_in_quadrant2_or3);
}