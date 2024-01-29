#include "../../../include/game/executors/PlayerExecutor.hpp"

#include "../../../include/game/entity/FightingEntityUtils.hpp"
#include "../../../include/geometry/GeomAuxiliaryFunc.hpp"
#include "../../../include/geometry/Trigonometry.hpp"

PlayerExecutor::PlayerExecutor(MouseLocator &&mouse_locator, const BulletCreator &bullet_creator,
        CollisionHandler &collision_handler, ItemChecker &item_handler,
        Player *const& player, QuadtreeEl &quadtree):
    _mouse_locator(std::move(mouse_locator)), _bullet_creator(bullet_creator),
    _collision_handler(&collision_handler), _item_handler(&item_handler),
    _player(&player), _quadtree(&quadtree) {}

bool PlayerExecutor::checkMovement(const Player &player, const int delta_time, sf::Vector2f &result) {
    const auto& character = player.getCharacter();
    const bool has_movement = MovementUtils::hasMovement(
        player.getControl().getMovementMask(),
        character.getStats().speed * static_cast<float>(delta_time),
        result
    );
    character.setSpriteIndex(has_movement);
    return has_movement;
}

bool PlayerExecutor::hasSelection(const Player& player) {
    return player.getControl().take_item.idPressed();
}

bool PlayerExecutor::hasShoot(const Player& player) {
    return player.getControl().fire.idPressed();
}

void PlayerExecutor::updatePlayer(Player &player, const int delta_time) const {
    sf::Vector2f movement_vector;
    if (const Action action(checkMovement(player, delta_time, movement_vector), hasSelection(player)); action.hasAnyAction())
        handleActions(player, action, movement_vector);
}

void PlayerExecutor::handleActions(Player& player, const Action &action, const sf::Vector2f& movement_vector) const {
    const auto& element = player.getCharacter().getElement();
    
    ElementCollisionSet element_collision_set;
    if (action.has_movement) { movePlayer(element, movement_vector, element_collision_set); }
    else                     { _quadtree->fillCollisionSet(element.getPolygon(), element_collision_set); }

    if (action.has_selection && player.canTakeNewGun()) {
        element_collision_set.erase(&player.getGun().getElement());
        _item_handler->checkTakingItem(player, element_collision_set);
    }
}

void PlayerExecutor::movePlayer(const Element &element, const sf::Vector2f &movement_vector,
        ElementCollisionSet &element_collision_set) const {
    _quadtree->remove(&element);
    element.move(movement_vector);
    _quadtree->fillCollisionSet(element.getPolygon(), element_collision_set);
    _collision_handler->handleCollisions(element, element_collision_set);
    _quadtree->insert(&element);
}

void PlayerExecutor::checkShoot(const Player &player) const {
    if (const auto& gun = player.getGun(); hasShoot(player) && gun.canFire())
        _bullet_creator.spawnBullet(gun.fire(), player.getCharacter().getElement());
}

void PlayerExecutor::handle(const int delta_time) {
    if (*_player) {
        Player& player = **_player;
        const auto mouse_pos(_mouse_locator.getMousePos());
        
        const auto destination(mouse_pos - FightingEntityUtils::calcCenter(player));
        const float angle(GeomAuxiliaryFunc::calcAngle(destination));
    
        player.checkMirror(Trigonometry::isAngleInQuadrant2Or3(angle));
        updatePlayer(player, delta_time);
        FightingEntityUtils::updateGun(player.getGun(), player.getGunPos(), angle, *_quadtree);
        checkShoot(player);
    }
}