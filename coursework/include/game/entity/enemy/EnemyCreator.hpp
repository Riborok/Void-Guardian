#pragma once
#include "../../../geometry/collision/CollisionManager.hpp"
#include "../../../quadtree/quadtree type defs/QuadtreeEl.hpp"
#include "../services/EntityCreator.hpp"

class EnemyCreator final {
    EntityCreator *_entity_creator;
    CollisionManager *_collision_manager;
    QuadtreeEl *_quadtree_el;
    static void freeEnemy(const Enemy *enemy);
public:
    EnemyCreator(EntityCreator &entity_creator, CollisionManager &collision_manager,
        QuadtreeEl &quadtree_el);
    [[nodiscard]] Enemy* spawnEnemy(const FightingEntityInfo &entity_info) const;
    
    ~EnemyCreator() noexcept = default;
    EnemyCreator(EnemyCreator&&) noexcept = default;
    EnemyCreator& operator=(EnemyCreator&&) noexcept = delete;
    EnemyCreator(const EnemyCreator&) noexcept = default;
    EnemyCreator& operator=(const EnemyCreator&) noexcept = delete;
};
