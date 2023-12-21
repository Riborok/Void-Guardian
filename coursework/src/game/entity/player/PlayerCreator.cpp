#include "../../../../include/game/entity/player/PlayerCreator.hpp"

PlayerCreator::PlayerCreator(PlayerMap &player_map, EntityCreator &entity_creator, QuadtreeEl &quadtree_el) :
    _player_map(&player_map), _entity_creator(&entity_creator), _quadtree_el(&quadtree_el) {}

void PlayerCreator::spawnPlayer(const FightingEntityInfo &player_info, const Control &control,
        const sf::Vector2f& offset_factor) const {
    auto* player = _entity_creator->createPlayer(player_info, control, offset_factor);
    _player_map->insert(player);
    _quadtree_el->insert(&player->getCharacter().getElement());
    _quadtree_el->insert(&player->getGun().getElement());
}
