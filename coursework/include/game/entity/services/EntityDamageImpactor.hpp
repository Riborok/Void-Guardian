#pragma once
#include "DyingEffectAnimator.hpp"
#include "../EntityMaps.hpp"
#include "../../GameState.hpp"
#include "../../../element/ElementCreator.hpp"
#include "../../../geometry/collision/ElementCollisionSet.hpp"
#include "../../../quadtree/quadtree type defs/QuadtreeEl.hpp"

class EntityDamageImpactor final {
    EntityMaps *_entity_maps;
    DyingEffectAnimator _dying_effect_animator;
    QuadtreeEl *_quadtree;
    GameState *_game_state;

    void removeFromQuadtree(const FightingEntity *fighting_entity) const;
    void removeFromQuadtree(const BulletCasing& bullet_casing) const;
    void applyDamage(const BulletHarm &bullet_harm, Player *player) const;
    void applyDamage(const BulletHarm &bullet_harm, Enemy *enemy) const;
    void applyDamage(const BulletCasing& bullet_casing, Bullet* other_bullet) const;
public:
    EntityDamageImpactor(EntityMaps& entity_maps, ElementCreator& element_creator,
            AnimationAttacher& animation_attacher, QuadtreeEl& quadtree, GameState &game_state);
    void applyDamage(const Bullet &bullet, const ElementCollisionSet &hits) const;
    [[nodiscard]] const DyingEffectAnimator& getDyingAnimator() const;
    
    ~EntityDamageImpactor() noexcept = default;
    EntityDamageImpactor(EntityDamageImpactor&&) noexcept = default;
    EntityDamageImpactor& operator=(EntityDamageImpactor&&) noexcept = delete;
    EntityDamageImpactor(const EntityDamageImpactor&) noexcept = delete;
    EntityDamageImpactor& operator=(const EntityDamageImpactor&) noexcept = delete;
};
