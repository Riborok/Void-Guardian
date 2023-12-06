﻿#include "../../../include/game/executors/PlayerExecutor.hpp"
#include "../../../include/geometry/GeomAuxiliaryFunc.hpp"
#include "../../../include/geometry/Trigonometry.hpp"

PlayerExecutor::PlayerExecutor(MouseLocator &&mouse_locator, BulletCreator &&bullet_creator, InputHandler& input_handler,
        CollisionManager &collision_manager, PlayerMap &player_map, QuadtreeEl& quadtree):
    _mouse_locator(std::move(mouse_locator)), _bullet_creator(std::move(bullet_creator)),
    _input_handler(&input_handler), _collision_manager(&collision_manager), _player_map(&player_map),
    _quadtree(&quadtree) {}

void PlayerExecutor::updateWraith(const Wraith &wraith, const Control &control, const int delta_time) const {
    sf::Vector2f result;
    const bool has_any_movement = hasMovement(
        control,
        *_input_handler,
        wraith.getStats().speed * static_cast<float>(delta_time),
        result
    );
    wraith.setSpriteIndex(has_any_movement);
    if (has_any_movement)
        moveWraith(wraith, result);
}

void PlayerExecutor::moveWraith(const Wraith &wraith, const sf::Vector2f &vector) const {
    const auto* element = &wraith.getElement();
    
    _quadtree->remove(element);
    wraith.getElement().move(vector);
    _collision_manager->processCollisions(*element, *_quadtree);
    _quadtree->insert(element);
}

void PlayerExecutor::updateGun(const Gun &gun, const sf::Vector2f &target_p, const float target_a) const {
    const auto* element = &gun.getElement();
    
    _quadtree->remove(element);
    gun.update(target_p, target_a);
    _quadtree->insert(element);
}

void PlayerExecutor::checkShoot(const Player &player) const {
    if (LaunchData launch_data; _input_handler->isDown(player.getControl().fire) && player.getGun().fire(launch_data)) {
        _bullet_creator.spawnBullet(launch_data, player.getWraith().getElement());
    }
}

void PlayerExecutor::handle(const int delta_time) {
    const auto mouse_pos(_mouse_locator.getMousePos());
    
    for (const auto& [id, player] : _player_map->getMap()) {
        const auto destination(mouse_pos - player->getWraith().getElement().getPolygon().calcCenter());
        const float angle(GeomAuxiliaryFunc::calcAngle(destination));
        
        player->checkMirror(Trigonometry::isAngleInQuadrant2Or3(angle));
        updateWraith(player->getWraith(), player->getControl(), delta_time);
        updateGun(player->getGun(), player->getGunPos(), angle);
        checkShoot(*player);
    }
}