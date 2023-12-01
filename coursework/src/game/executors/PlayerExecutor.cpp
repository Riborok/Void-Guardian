#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "../../../include/game/executors/PlayerExecutor.hpp"
#include "../../../include/geometry/GeomAuxiliaryFunc.hpp"
#include "../../../include/geometry/Trigonometry.hpp"

PlayerExecutor::PlayerExecutor(sf::RenderWindow &window, InputHandler& input_handler,
        CollisionManager &collision_manager, PlayerMap &player_map, QuadtreeEl& quadtree):
    _window(&window), _input_handler(&input_handler), _collision_manager(&collision_manager),
    _player_map(&player_map), _quadtree(&quadtree) {}

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

void PlayerExecutor::handle(const int delta_time) {
    const auto mouse_pos(_window->mapPixelToCoords(sf::Mouse::getPosition(*_window)));
    
    for (auto& [id, player] : _player_map->getMap()) {
        const auto destination(mouse_pos - player->getWraith().getElement().getPolygon().calcCenter());
        const float angle(GeomAuxiliaryFunc::calcAngle(destination));
        
        player->checkMirror(Trigonometry::isAngleInQuadrant2Or3(angle));
        updateWraith(player->getWraith(), player->getControl(), delta_time);
        updateGun(player->getGun(), player->getGunPos(), angle);
    }
}