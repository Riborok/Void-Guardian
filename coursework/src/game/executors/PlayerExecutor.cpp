#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "../../../include/game/executors/PlayerExecutor.hpp"
#include "../../../include/geometry/GeomAuxiliaryFunc.hpp"
#include "../../../include/geometry/Trigonometry.hpp"

PlayerExecutor::PlayerExecutor(sf::RenderWindow &window, KeyHandler& key_handler, CollisionManager &collision_resolution, QuadtreeEl& quadtree)
    : _window(&window), _key_handler(&key_handler), _collision_resolution(&collision_resolution), _quadtree(&quadtree) {}

void PlayerExecutor::addPlayer(Player* player) { _players.push_back(player); }

void PlayerExecutor::updateWraith(const Wraith &wraith, const Control &control, const int delta_time) const {
    sf::Vector2f result;
    const bool has_any_movement = hasMovement(
        control,
        *_key_handler,
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
    _collision_resolution->processCollisions(*element, *_quadtree);
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
    
    for (auto* player : _players) {
        const auto destination(mouse_pos - player->getWraith().getElement().getPolygon().calcCenter());
        const float angle(GeomAuxiliaryFunc::calcAngle(destination));
        
        player->checkMirror(Trigonometry::isAngleInQuadrant2Or3(angle));
        updateWraith(player->getWraith(), player->getControl(), delta_time);
        updateGun(player->getGun(), player->getGunPos(), angle);
    }
}

PlayerExecutor::~PlayerExecutor() noexcept {
    for (const auto* player : _players)
        delete player;
}