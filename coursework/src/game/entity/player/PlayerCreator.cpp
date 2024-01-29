#include "../../../../include/game/entity/player/PlayerCreator.hpp"

PlayerCreator::PlayerCreator(EntityCreator &entity_creator, CollisionHandler &collision_handler, QuadtreeEl &quadtree_el) :
    _entity_creator(&entity_creator), _collision_handler(&collision_handler), _quadtree_el(&quadtree_el) {}

Player* PlayerCreator::spawnPlayer(const FightingEntityInfo &player_info, const Control &control,
        const sf::Vector2f& offset_factor) const {
    auto* player = _entity_creator->createPlayer(player_info, control, offset_factor);
    if (_collision_handler->handleCollisions(player->getCharacter().getElement(), *_quadtree_el))
        player->getGun().update(player->getGunPos());
    _quadtree_el->insert(&player->getCharacter().getElement());
    _quadtree_el->insert(&player->getGun().getElement());
    return player;
}