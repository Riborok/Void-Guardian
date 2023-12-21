#include "../../../include/game/executors/PlayerExecutor.hpp"
#include "../../../include/geometry/GeomAuxiliaryFunc.hpp"
#include "../../../include/geometry/Trigonometry.hpp"

PlayerExecutor::PlayerExecutor(MouseLocator &&mouse_locator, BulletCreator &&bullet_creator, InputHandler& input_handler,
        CollisionManager &collision_manager, CollectibleManager &collectible_manager,
        Player *const& player, QuadtreeEl &quadtree):
    _mouse_locator(std::move(mouse_locator)), _bullet_creator(std::move(bullet_creator)),
    _input_handler(&input_handler), _collision_manager(&collision_manager),
    _collectible_manager(&collectible_manager), _player(&player), _quadtree(&quadtree) {}

bool PlayerExecutor::checkMovement(const Player &player, const int delta_time, sf::Vector2f &result) const {
    const auto& character = player.getCharacter();
    const bool has_movement = hasMovement(
        player.getControl(),
        *_input_handler,
        character.getStats().speed * static_cast<float>(delta_time),
        result
    );
    character.setSpriteIndex(has_movement);
    return has_movement;
}

bool PlayerExecutor::checkSelection(const Player& player) const {
    return _input_handler->isDown(player.getControl().take_collectible);
}

void PlayerExecutor::updatePlayer(Player &player, const int delta_time) const {
    sf::Vector2f movement_vector;
    const Action action(checkMovement(player, delta_time, movement_vector), checkSelection(player));
    if (action.hasAnyAction())
        processActions(player, action, movement_vector);
}

void PlayerExecutor::processActions(Player& player, const Action &action, const sf::Vector2f& movement_vector) const {
    const auto& element = player.getCharacter().getElement();
    
    ElementCollisionSet element_collision_set;
    if (action.has_movement)
        movePlayer(element, movement_vector, element_collision_set);
    else
        _quadtree->fillCollisionSet(element.getPolygon(), element_collision_set);

    if (action.has_selection && player.canTakeNewGun()) {
        element_collision_set.erase(&player.getGun().getElement());
        _collectible_manager->checkCollectibleSelection(player, element_collision_set);
    }
}

void PlayerExecutor::movePlayer(const Element &element, const sf::Vector2f &movement_vector,
        ElementCollisionSet &element_collision_set) const {
    _quadtree->remove(&element);
    element.move(movement_vector);
    _quadtree->fillCollisionSet(element.getPolygon(), element_collision_set);
    _collision_manager->processCollisions(element, element_collision_set);
    _quadtree->insert(&element);
}

void PlayerExecutor::updateGun(const Gun &gun, const sf::Vector2f &target_p, const float target_a) const {
    const auto* element = &gun.getElement();
    
    _quadtree->remove(element);
    gun.update(target_p, target_a);
    _quadtree->insert(element);
}

void PlayerExecutor::checkShoot(const Player &player) const {
    if (const auto& gun = player.getGun(); _input_handler->isDown(player.getControl().fire) && gun.canFire())
        _bullet_creator.spawnBullet(gun.fire(), player.getCharacter().getElement());
}

void PlayerExecutor::handle(const int delta_time) {
    if (*_player) {
        Player& player = **_player;
        const auto mouse_pos(_mouse_locator.getMousePos());
        
        const auto destination(mouse_pos - player.getCharacter().getElement().getPolygon().calcCenter());
        const float angle(GeomAuxiliaryFunc::calcAngle(destination));
    
        player.checkMirror(Trigonometry::isAngleInQuadrant2Or3(angle));
        updatePlayer(player, delta_time);
        updateGun(player.getGun(), player.getGunPos(), angle);
        checkShoot(player);
    }
}