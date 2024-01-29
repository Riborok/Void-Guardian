#pragma once
#include "Executor.hpp"
#include "../../geometry/collision/CollisionHandler.hpp"
#include "../entity/services/EntityDamageImpactor.hpp"
#include "../entity/EntityMaps.hpp"

class BulletExecutor final : public Executor {
    CollisionHandler *_collision_handler;
    BulletMap *_bullet_map;
    QuadtreeEl *_quadtree;
    EntityDamageImpactor _entity_damage_impactor;

    void evaluateBulletMotion(const BulletCasing &bullet_casing, const sf::Vector2f &velocity,
        ElementCollisionSet &element_collision_set) const;
    void moveBullet(const Bullet& bullet, const int delta_time, ElementCollisionSet &element_collision_set) const;
    void handleBullet(BulletMap::ConstIterator &iterator, const int delta_time) const;
public:
    BulletExecutor(CollisionHandler &collision_handler, BulletMap &bullet_map,
        QuadtreeEl& quadtree, EntityDamageImpactor &&entity_damage_impactor);
    void handle(const int delta_time) override;
    
    ~BulletExecutor() noexcept override = default;
    BulletExecutor(BulletExecutor&&) noexcept = default;
    BulletExecutor& operator=(BulletExecutor&&) noexcept = delete;
    BulletExecutor(const BulletExecutor&) noexcept = delete;
    BulletExecutor& operator=(const BulletExecutor&) noexcept = delete;
};
