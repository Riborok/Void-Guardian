#include "../../../include/game/managers/CollectibleManager.hpp"

CollectibleManager::CollectibleManager(GunManager& gun_manager, const QuadtreeLoc& quadtree_loc):
    _gun_manager(&gun_manager), _quadtree_loc(&quadtree_loc) {}

void CollectibleManager::processSelection(Player &player, const Element &element) const {
    switch (ElementIdTracker::extractType(element.getId())) {
    case ElementType::GUN:
        _gun_manager->swapGuns(player, element);
        break;
    case ElementType::PORTAL:

        break;
    default: ;
    }
}

void CollectibleManager::checkCollectibleSelection(Player& player, const ElementCollisionSet& collision_set) const {
    for (const auto *collision : collision_set)
        if (ElementIdTracker::isCollectible(collision->getId()))
            processSelection(player, *collision);
}
