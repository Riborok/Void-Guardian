#pragma once
#include "PlayerMap.hpp"
#include "../EntityCreator.hpp"
#include "../../../quadtree/quadtree type defs/QuadtreeEl.hpp"

class PlayerCreator final {
    PlayerMap *_bullet_map;
    EntityCreator *_entity_creator;
    QuadtreeEl *_quadtree_el;
public: 
    PlayerCreator(PlayerMap &bullet_map, EntityCreator &entity_creator, QuadtreeEl &quadtree_el);
    void spawnPlayer(const PlayerInfo &player_info, const Control &control, const sf::Vector2f& offset_factor) const;
    
    ~PlayerCreator() noexcept = default;
    PlayerCreator(PlayerCreator&&) noexcept = default;
    PlayerCreator& operator=(PlayerCreator&&) noexcept = delete;
    PlayerCreator(const PlayerCreator&) noexcept = delete;
    PlayerCreator& operator=(const PlayerCreator&) noexcept = delete;
};
