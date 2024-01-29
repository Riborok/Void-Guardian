#pragma once
#include "../../../geometry/collision/CollisionHandler.hpp"
#include "../../../quadtree/quadtree type defs/QuadtreeEl.hpp"
#include "../services/EntityCreator.hpp"

class EnemyCreator final {
    EntityCreator *_entity_creator;
    CollisionHandler *_collision_handler;
    QuadtreeEl *_quadtree_el;
    static void freeEnemy(const Enemy *enemy);
public:
    EnemyCreator(EntityCreator &entity_creator, CollisionHandler &collision_handler,
        QuadtreeEl &quadtree_el);
    [[nodiscard]] Enemy* spawnEnemy(const FightingEntityInfo &entity_info) const;
    
    ~EnemyCreator() noexcept = default;
    EnemyCreator(EnemyCreator&&) noexcept = default;
    EnemyCreator& operator=(EnemyCreator&&) noexcept = delete;
    EnemyCreator(const EnemyCreator&) noexcept = default;
    EnemyCreator& operator=(const EnemyCreator&) noexcept = delete;
};
