#pragma once
#include "EntityMaps.hpp"
#include "../../element/ElementCreator.hpp"
#include "../../geometry/collision/ElementCollisionSet.hpp"
#include "../../quadtree/quadtree type defs/QuadtreeEl.hpp"

class EntityDamageManager final {
    EntityMaps *_entity_maps;
    ElementCreator *_element_creator;
    AnimationExecutor *_animation_executor;
    QuadtreeEl *_quadtree;

    void erase(const Player *player) const;
    void erase(const Bullet *bullet) const;
public:
    EntityDamageManager(EntityMaps& entity_maps, ElementCreator& element_creator,
            AnimationExecutor& animation_executor, QuadtreeEl& quadtree);
    void applyDamage(const BulletStats &bullet_stats, const ElementCollisionSet &hits) const;
    void createAnimation(const Player &player) const;
    void createAnimation(const Bullet &bullet) const;
    
    ~EntityDamageManager() noexcept = default;
    EntityDamageManager(EntityDamageManager&&) noexcept = default;
    EntityDamageManager& operator=(EntityDamageManager&&) noexcept = default;
    EntityDamageManager(const EntityDamageManager&) noexcept = delete;
    EntityDamageManager& operator=(const EntityDamageManager&) noexcept = delete;
};
