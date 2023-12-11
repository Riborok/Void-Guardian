#include "../../../../../include/game/entity/player/gun/GunManager.hpp"

#include "../../../../../include/geometry/Trigonometry.hpp"

const sf::Vector2f GunManager::OFFSET_FACTOR{-0.5f, -0.5f};

GunManager::GunManager(const EntityCreator &entity_creator, QuadtreeEl &quadtree):
    _entity_creator(&entity_creator), _quadtree(&quadtree){}

void GunManager::createGun(const sf::Vector2f& p, const int num) {
    Gun gun(_entity_creator->createGun(p, LEAN, num, OFFSET_FACTOR));
    _quadtree->insert(&_guns.emplace(gun.getId(), std::move(gun)).first->second.getElement());
}

void GunManager::setWeaponSettings(const Gun &gun) const {
    auto &element = gun.getElement();

    element.rotate(element.getPolygon().getPoints()[0], LEAN - element.getPolygon().getRotation());
    if (element.isMirroredHor())
        element.mirrorHor();
    
    _entity_creator->setDefaultZIndex(element, gun.geNum());
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