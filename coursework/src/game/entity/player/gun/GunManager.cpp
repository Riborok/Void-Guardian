#include "../../../../../include/game/entity/player/gun/GunManager.hpp"
#include "../../../../../include/geometry/Trigonometry.hpp"

GunManager::GunManager(const EntityCreator &entity_creator, const CollisionManager &collision_manager, QuadtreeEl &quadtree):
    _entity_creator(&entity_creator), _collision_manager(&collision_manager), _quadtree(&quadtree){}

void GunManager::createGun(const sf::Vector2f& p, const int num) {
    Gun gun(_entity_creator->createGun(p, LEAN, num, _offset_factor));
    _quadtree->insert(&_guns.emplace(gun.getId(), std::move(gun)).first->second.getElement());
}

void GunManager::setAngle(Element &element) {
    element.rotate(element.getPolygon().getPoints()[0], LEAN - element.getPolygon().getRotation());
    if (element.isMirroredHor())
        element.mirrorHor();
}

void GunManager::processCollisions(const Element &element) const {
    ElementCollisionSet element_collision_set;
    _quadtree->fillCollisionSet(element.getPolygon(), element_collision_set);
    _collision_manager->processCollisions(element, element_collision_set);
}

void GunManager::setWeaponSettings(const Gun &gun) const {
    auto &element = gun.getElement();
    setAngle(element);
    processCollisions(element);
    _entity_creator->setDefaultZIndex(element, gun.getNum());
}

void GunManager::swapGuns(Player &player, const Element &gun) {
    if (const auto it = _guns.find(gun.getId()); it != _guns.end()) {
        Gun player_gun = player.takeNewGun(std::move(it->second));
        _guns.erase(it);
        
        _quadtree->remove(&player_gun.getElement());
        setWeaponSettings(player_gun);
        _quadtree->insert(&_guns.emplace(player_gun.getId(), std::move(player_gun)).first->second.getElement());
    }
}