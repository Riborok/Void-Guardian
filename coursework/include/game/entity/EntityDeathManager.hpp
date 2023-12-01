#pragma once
#include "EntityMaps.hpp"
#include "../../element/ElementCreator.hpp"
#include "../../quadtree/quadtree type defs/QuadtreeEl.hpp"

class EntityDeathManager final {
    EntityMaps *_entity_maps;
    ElementCreator *_element_creator;
    AnimationExecutor *_animation_executor;
    QuadtreeEl *_quadtree;

    void processMurder(const Player *player) const;
    void processMurder(const Bullet *bullet) const;
public:
    EntityDeathManager(EntityMaps& entity_maps, ElementCreator& element_creator,
            AnimationExecutor& animation_executor, QuadtreeEl& quadtree);
    void kill(const Entity *entity) const;
    
    ~EntityDeathManager() noexcept = default;
    EntityDeathManager(EntityDeathManager&&) noexcept = default;
    EntityDeathManager& operator=(EntityDeathManager&&) noexcept = default;
    EntityDeathManager(const EntityDeathManager&) noexcept = delete;
    EntityDeathManager& operator=(const EntityDeathManager&) noexcept = delete;
};
