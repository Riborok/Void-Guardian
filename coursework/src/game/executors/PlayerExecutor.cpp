#include <SFML/Window/Mouse.hpp>

#include "../../../include/game/executors/PlayerExecutor.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

PlayerExecutor::PlayerExecutor(sf::RenderWindow &window, KeyHandler& key_handler, CollisionManager &collision_resolution, QuadtreeEl& quadtree)
    : _window(&window), _key_handler(&key_handler), _collision_resolution(&collision_resolution), _quadtree(&quadtree) {}

void PlayerExecutor::addPlayer(Player* player) {
    _players.push_back(player);
}

void PlayerExecutor::handle(const int delta_time) {
    const auto mouse_position(_window->mapPixelToCoords(sf::Mouse::getPosition(*_window)));
    
    for (auto* player : _players) {
        const bool is_moved = _key_handler->isKeyDown(player->getControl().move);
        player->setSpriteIndex(is_moved);
        if (is_moved) {
            auto* element = &player->getElement();
            _quadtree->remove(element);
            player->move(mouse_position, delta_time);
            _collision_resolution->processCollisions(*element, *_quadtree);
            _quadtree->insert(element);
        }
    }
}

PlayerExecutor::~PlayerExecutor() noexcept {
    for (const auto* player : _players)
        delete player;
}