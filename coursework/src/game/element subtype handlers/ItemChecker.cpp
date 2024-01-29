// ReSharper disable CppIncompleteSwitchStatement CppDefaultCaseNotHandledInSwitchStatement
#include "../../../include/game/element subtype handlers/ItemChecker.hpp"

#include "../../../include/game/identifiable/LocationIdTracker.hpp"

ItemChecker::ItemChecker(GunInstaller& gun_installer, const QuadtreeLoc& quadtree_loc, GameState &game_state):
    _gun_installer(&gun_installer), _quadtree_loc(&quadtree_loc), _game_state(&game_state) {}

void ItemChecker::handleSelection(Player &player, const Element &element) const {
    switch (ElementIdTracker::extractType(element.getId())) {
    case ElementType::GUN:
        _gun_installer->swapGuns(player, element);
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

void ItemChecker::checkTakingItem(Player& player, const ElementCollisionSet& collision_set) const {
    for (const auto *collision : collision_set)
        if (ElementIdTracker::isItem(collision->getId()))
            handleSelection(player, *collision);
}
