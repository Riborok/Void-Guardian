#pragma once
#include "Executor.hpp"
#include "../../geometry/collision/CollisionManager.hpp"
#include "../entity/EntityDamageManager.hpp"
#include "../entity/EntityMaps.hpp"

class BulletExecutor final : public Executor {
    CollisionManager *_collision_manager;
    BulletMap *_bullet_map;
    QuadtreeEl *_quadtree;
    EntityDamageManager _entity_damage_manager;

    void evaluateBulletMotion(const Bullet &bullet, const sf::Vector2f &velocity,
        ElementCollisionSet &element_collision_set) const;
    void moveBullet(const Bullet& bullet, const int delta_time, ElementCollisionSet &element_collision_set) const;
    void handleBullet(BulletMap::ConstIterator &iterator, const int delta_time) const;
public:
    BulletExecutor(CollisionManager &collision_manager, BulletMap &bullet_map,
        QuadtreeEl& quadtree, EntityDamageManager &&entity_damage_manager);
    void handle(const int delta_time) override;
    
    ~BulletExecutor() noexcept override = default;
    BulletExecutor(BulletExecutor&&) noexcept = default;
    BulletExecutor& operator=(BulletExecutor&&) noexcept = delete;
    BulletExecutor(const BulletExecutor&) noexcept = delete;
    BulletExecutor& operator=(const BulletExecutor&) noexcept = delete;
};
