#pragma once
#include "BulletMap.hpp"
#include "../services/EntityCreator.hpp"
#include "../../../quadtree/quadtree type defs/QuadtreeEl.hpp"

class BulletCreator final {
    BulletMap *_bullet_map;
    EntityCreator *_entity_creator;
    QuadtreeEl *_quadtree_el;
    
    static float getOverlap(const Element &bullet_element, const Element &character_bullet_collision,
        const sf::Vector2f &collision_normal);
    static void processEstimatedCollision(const Element &bullet_element, const Element &character_bullet_collision);
public:
    BulletCreator(BulletMap &bullet_map, EntityCreator &entity_creator, QuadtreeEl &quadtree_el);
    void spawnBullet(const LaunchData &launch_data, const Element &character_bullet_collision) const;
    
    ~BulletCreator() noexcept = default;
    BulletCreator(BulletCreator&&) noexcept = default;
    BulletCreator& operator=(BulletCreator&&) noexcept = delete;
    BulletCreator(const BulletCreator&) noexcept = delete;
    BulletCreator& operator=(const BulletCreator&) noexcept = delete;
};
