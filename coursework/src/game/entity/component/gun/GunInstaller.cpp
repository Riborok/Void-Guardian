#include "../../../../../include/game/entity/component/gun/GunInstaller.hpp"
#include "../../../../../include/geometry/Trigonometry.hpp"

GunInstaller::GunInstaller(const EntityCreator &entity_creator, const CollisionHandler &collision_handler, QuadtreeEl &quadtree):
    _entity_creator(&entity_creator), _collision_handler(&collision_handler), _quadtree(&quadtree){}

void GunInstaller::createGun(const sf::Vector2f& p, const size_t num) {
    Gun gun(_entity_creator->createGun(p, LEAN, num, _offset_factor));
    _quadtree->insert(&_guns.emplace(gun.getId(), std::move(gun)).first->second.getElement());
}

void GunInstaller::setAngle(Element &element) {
    element.rotate(element.getPolygon().getPoints()[0], LEAN - element.getPolygon().getRotation());
    if (element.isMirroredHor())
        element.mirrorHor();
}

void GunInstaller::setWeaponSettings(const Gun &gun) const {
    auto &element = gun.getElement();
    setAngle(element);
    _collision_handler->handleCollisions(element, *_quadtree);
    _entity_creator->setDefaultZIndex(element, gun.getNum());
}

void GunInstaller::swapGuns(Player &player, const Element &gun) {
    if (const auto it = _guns.find(gun.getId()); it != _guns.end()) {
        Gun player_gun = player.takeNewGun(std::move(it->second));
        _guns.erase(it);
        
        _quadtree->remove(&player_gun.getElement());
        setWeaponSettings(player_gun);
        _quadtree->insert(&_guns.emplace(player_gun.getId(), std::move(player_gun)).first->second.getElement());
    }
}