#include "../../../../include/game/entity/player/PlayerCreator.hpp"

PlayerCreator::PlayerCreator(PlayerMap &bullet_map, EntityCreator &entity_creator, QuadtreeEl &quadtree_el) :
    _bullet_map(&bullet_map), _entity_creator(&entity_creator), _quadtree_el(&quadtree_el) {}

void PlayerCreator::spawnPlayer(const PlayerInfo &player_info, const sf::Vector2f& offset_factor) const {
    auto* player = _entity_creator->createPlayer(player_info, offset_factor);
    _bullet_map->insert(player);
    _quadtree_el->insert(&player->getWraith().getElement());
    _quadtree_el->insert(&player->getGun().getElement());
}
