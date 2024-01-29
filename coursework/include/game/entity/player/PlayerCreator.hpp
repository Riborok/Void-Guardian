#pragma once
#include "../../../geometry/collision/CollisionHandler.hpp"
#include "../services/EntityCreator.hpp"
#include "../../../quadtree/quadtree type defs/QuadtreeEl.hpp"

class PlayerCreator final {
    EntityCreator *_entity_creator;
    CollisionHandler *_collision_handler;
    QuadtreeEl *_quadtree_el;
public: 
    PlayerCreator(EntityCreator &entity_creator, CollisionHandler &collision_handler, QuadtreeEl &quadtree_el);
    [[nodiscard]] Player* spawnPlayer(const FightingEntityInfo &player_info, const Control &control, const sf::Vector2f& offset_factor) const;
    
    ~PlayerCreator() noexcept = default;
    PlayerCreator(PlayerCreator&&) noexcept = default;
    PlayerCreator& operator=(PlayerCreator&&) noexcept = delete;
    PlayerCreator(const PlayerCreator&) noexcept = delete;
    PlayerCreator& operator=(const PlayerCreator&) noexcept = delete;
};
