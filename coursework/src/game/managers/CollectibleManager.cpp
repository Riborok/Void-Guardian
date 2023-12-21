// ReSharper disable CppIncompleteSwitchStatement CppDefaultCaseNotHandledInSwitchStatement
#include "../../../include/game/managers/CollectibleManager.hpp"

#include "../../../include/game/identifiable/LocationIdTracker.hpp"

CollectibleManager::CollectibleManager(GunManager& gun_manager, const QuadtreeLoc& quadtree_loc, GameState &game_state):
    _gun_manager(&gun_manager), _quadtree_loc(&quadtree_loc), _game_state(&game_state) {}

void CollectibleManager::processSelection(Player &player, const Element &element) const {
    switch (ElementIdTracker::extractType(element.getId())) {
    case ElementType::GUN:
        _gun_manager->swapGuns(player, element);
        break;
    case ElementType::PORTAL: {
        CollisionResult collision_result;
        const auto *location = _quadtree_loc->getCollision(player.getCharacter().getElement().getPolygon(), collision_result);
        if (const RoomType type = LocationIdTracker::extractType(location->getId()); type == RoomType::SPAWN)
            *_game_state = GameState::RETURN_TO_MENU;
        else if (type == RoomType::PORTAL)
            *_game_state = GameState::NEXT_LEVEL;
        break;
    }
    }
}

void CollectibleManager::checkCollectibleSelection(Player& player, const ElementCollisionSet& collision_set) const {
    for (const auto *collision : collision_set)
        if (ElementIdTracker::isCollectible(collision->getId()))
            processSelection(player, *collision);
}
