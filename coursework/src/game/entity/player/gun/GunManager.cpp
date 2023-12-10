#include "../../../../../include/game/entity/player/gun/GunManager.hpp"

#include "../../../../../include/geometry/Trigonometry.hpp"

GunManager::GunManager(const EntityCreator &entity_creator, QuadtreeEl &quadtree):
    _entity_creator(&entity_creator), _quadtree(&quadtree){}

void GunManager::createGun(const sf::Vector2f& p, const int num) {
    Gun gun(_entity_creator->createGun(p, LEAN, num, {-0.5f, -0.5f}));
    _quadtree->insert(&_guns.emplace(gun.getId(), std::move(gun)).first->second.getElement());
}

void GunManager::setWeaponSettings(const Gun &gun) const {
    const auto &element = gun.getElement();
    
    const float delta_angle = element.isMirroredHor()
        ? Trigonometry::M_PI_ + (LEAN - element.getPolygon().getRotation())
        : LEAN - element.getPolygon().getRotation();
    element.rotate(element.getPolygon().getPoints()[0], delta_angle);
    
    _entity_creator->setDefaultZIndex(element, gun.geNum());
}

void GunManager::swapGuns(Player &player, const Element &gun) {
    if (const auto it = _guns.find(gun.getId()); it != _guns.end()) {
        Gun player_gun = player.takeNewGun(std::move(_guns.erase(it)->second));
        _quadtree->remove(&player_gun.getElement());
        setWeaponSettings(player_gun);
        _quadtree->insert(&_guns.emplace(player_gun.getId(), std::move(player_gun)).first->second.getElement());
    }
}