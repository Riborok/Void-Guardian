#pragma once
#include "Executor.hpp"
#include "../../geometry/collision/CollisionManager.hpp"
#include "../entity/EntityDeathManager.hpp"
#include "../entity/EntityMaps.hpp"

class BulletExecutor final : public Executor {
    CollisionManager *_collision_manager;
    BulletMap *_bullet_map;
    EntityDeathManager _entity_death_manager;
public:
    BulletExecutor(CollisionManager &collision_manager, BulletMap &bullet_map, EntityDeathManager &&entity_death_manager);
    
    void handle(const int delta_time) override;
    
    ~BulletExecutor() noexcept override = default;
    BulletExecutor(BulletExecutor&&) noexcept = default;
    BulletExecutor& operator=(BulletExecutor&&) noexcept = default;
    BulletExecutor(const BulletExecutor&) noexcept = delete;
    BulletExecutor& operator=(const BulletExecutor&) noexcept = delete;
};
