#include <SFML/Window/Mouse.hpp>

#include "../../../include/game/executors/PlayerExecutor.hpp"

PlayerExecutor::PlayerExecutor(Quadtree<Element>& quadtree, KeyHandler& key_handler)
    : _quadtree(&quadtree), _key_handler(&key_handler) {}

void PlayerExecutor::addPlayer(Player* player) {
    _players.push_back(player);
}

void PlayerExecutor::handle(const int delta_time) {
    const auto mouse_position = static_cast<sf::Vector2f>(sf::Mouse::getPosition());
    for (auto* player : _players) {
        const bool is_moved = _key_handler->isKeyDown(player->getControl().move);
        player->setSpriteIndex(is_moved);
        if (is_moved) {
            auto* element = &player->getElement();
            _quadtree->remove(element);
            player->move(mouse_position, delta_time);
            _quadtree->insert(element);
        }
    }
}

PlayerExecutor::~PlayerExecutor() noexcept {
    for (const auto* player : _players)
        delete player;
}