﻿#pragma once
#include "DyingEffectAnimator.hpp"
#include "../EntityMaps.hpp"
#include "../../GameState.hpp"
#include "../../../element/ElementCreator.hpp"
#include "../../../geometry/collision/ElementCollisionSet.hpp"
#include "../../../quadtree/quadtree type defs/QuadtreeEl.hpp"

class EntityDamageManager final {
    EntityMaps *_entity_maps;
    DyingEffectAnimator _dying_effect_animator;
    QuadtreeEl *_quadtree;
    GameState *_game_state;

    void removeFromQuadtree(const FightingEntity *fighting_entity) const;
    void removeFromQuadtree(const BulletCasing& bullet_casing) const;
    void applyDamage(const BulletStats &bullet_stats, Player *player) const;
    void applyDamage(const BulletStats &bullet_stats, Enemy *enemy) const;
    void applyDamage(const BulletCasing& bullet_casing, Bullet* other_bullet) const;
public:
    EntityDamageManager(EntityMaps& entity_maps, ElementCreator& element_creator,
            AnimationManager& animation_manager, QuadtreeEl& quadtree, GameState &game_state);
    void applyDamage(const Bullet &bullet, const ElementCollisionSet &hits) const;
    [[nodiscard]] const DyingEffectAnimator& getDyingAnimator() const;
    
    ~EntityDamageManager() noexcept = default;
    EntityDamageManager(EntityDamageManager&&) noexcept = default;
    EntityDamageManager& operator=(EntityDamageManager&&) noexcept = delete;
    EntityDamageManager(const EntityDamageManager&) noexcept = delete;
    EntityDamageManager& operator=(const EntityDamageManager&) noexcept = delete;
};
