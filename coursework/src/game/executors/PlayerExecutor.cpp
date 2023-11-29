// ReSharper disable CppClangTidyHicppMultiwayPathsCovered CppDefaultCaseNotHandledInSwitchStatement
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "../../../include/game/executors/PlayerExecutor.hpp"
#include "../../../include/geometry/GeomAuxiliaryFunc.hpp"
#include "../../../include/geometry/Trigonometry.hpp"
#include "../../../include/geometry/Vector2Rotation.hpp"

PlayerExecutor::PlayerExecutor(sf::RenderWindow &window, KeyHandler& key_handler, CollisionManager &collision_resolution, QuadtreeEl& quadtree)
    : _window(&window), _key_handler(&key_handler), _collision_resolution(&collision_resolution), _quadtree(&quadtree) {}

void PlayerExecutor::addPlayer(Player* player) {
    _players.push_back(player);
}

bool PlayerExecutor::hasMovement(sf::Vector2f& destination, const MovementMask movement_mask) {
    switch (movement_mask) {
        case 0b0000:
        case 0b1111:
        case 0b1100:
        case 0b0011:
            return false;
            
        case 0b0001:
        case 0b1101:
            break;

        case 0b0010:
        case 0b1110:
            Vector2Rotation::rotate180Degrees(destination);
            break;

        case 0b0100:
        case 0b0111:
            Vector2Rotation::rotate270Degrees(destination);
            break;

        case 0b1000:
        case 0b1011:
            Vector2Rotation::rotate90Degrees(destination);
            break;

        case 0b0101:
            Vector2Rotation::rotate45Degrees(destination);
            break;

        case 0b1001:
            Vector2Rotation::rotate135Degrees(destination);
            break;

        case 0b0110:
            Vector2Rotation::rotate315Degrees(destination);
            break;

        case 0b1010:
            Vector2Rotation::rotate225Degrees(destination);
            break;
    }
    return true;
}

void PlayerExecutor::updateWraith(const Wraith &wraith, sf::Vector2f &destination,
        const int delta_time, const Control &control) const {
    const bool has_any_movement = hasMovement(destination, getMovementMask(control, *_key_handler));
    
    wraith.setSpriteIndex(has_any_movement);
    if (has_any_movement)
        moveWraith(wraith, destination, delta_time);
}

void PlayerExecutor::moveWraith(const Wraith &wraith, const sf::Vector2f &destination, const int delta_time) const {
    const auto* element = &wraith.getElement();
    
    _quadtree->remove(element);
    wraith.move(destination, delta_time);
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
        auto destination(player->getWraith().calcRelativePos(mouse_pos));
        const float angle(GeomAuxiliaryFunc::calcAngle(destination));
        
        player->checkMirror(Trigonometry::isAngleInQuadrant2Or3(angle));
        updateWraith(player->getWraith(), destination, delta_time, player->getControl());
        updateGun(player->getGun(), player->getGunPos(), angle);
    }
}

PlayerExecutor::~PlayerExecutor() noexcept {
    for (const auto* player : _players)
        delete player;
}