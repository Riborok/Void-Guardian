#pragma once
#include "EnemyMap.hpp"
#include "../../../quadtree/quadtree type defs/QuadtreeEl.hpp"
#include "../services/EntityCreator.hpp"

class EnemyCreator {
    EnemyMap *_enemy_map;
    EntityCreator *_entity_creator;
    QuadtreeEl *_quadtree_el;
public:
    EnemyCreator(EnemyMap &enemy_map, EntityCreator &entity_creator, QuadtreeEl &quadtree_el);
    void spawnEnemy(const FightingEntityInfo &player_info) const;
    
    ~EnemyCreator() noexcept = default;
    EnemyCreator(EnemyCreator&&) noexcept = default;
    EnemyCreator& operator=(EnemyCreator&&) noexcept = delete;
    EnemyCreator(const EnemyCreator&) noexcept = delete;
    EnemyCreator& operator=(const EnemyCreator&) noexcept = delete;
};
