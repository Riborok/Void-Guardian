#pragma once
#include "DyingEffectAnimator.hpp"
#include "EntityMaps.hpp"
#include "../../element/ElementCreator.hpp"
#include "../../geometry/collision/ElementCollisionSet.hpp"
#include "../../quadtree/quadtree type defs/QuadtreeEl.hpp"

class EntityDamageManager final {
    EntityMaps *_entity_maps;
    DyingEffectAnimator _dying_effect_animator;
    QuadtreeEl *_quadtree;

    void erase(const Player *player) const;
    void erase(const Bullet *bullet) const;
public:
    EntityDamageManager(EntityMaps& entity_maps, ElementCreator& element_creator,
            AnimationExecutor& animation_executor, QuadtreeEl& quadtree);
    void applyDamage(const Bullet &bullet, const ElementCollisionSet &hits) const;
    [[nodiscard]] const DyingEffectAnimator& getDyingAnimator() const;
    
    ~EntityDamageManager() noexcept = default;
    EntityDamageManager(EntityDamageManager&&) noexcept = default;
    EntityDamageManager& operator=(EntityDamageManager&&) noexcept = delete;
    EntityDamageManager(const EntityDamageManager&) noexcept = delete;
    EntityDamageManager& operator=(const EntityDamageManager&) noexcept = delete;
};
