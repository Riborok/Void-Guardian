#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Mouse.hpp>

#include "../../additionally/Types.h"
#include "../input/KeyHandler.h"
#include "../player/Player.h"

class PlayerExecutor final : public Types::Executor {
    Quadtree<Element> *_quadtree;
    KeyHandler *_key_handler;
    std::vector<Player*> _players;
public:
    PlayerExecutor(Quadtree<Element> &quadtree, KeyHandler &key_handler) : _quadtree(&quadtree), _key_handler(&key_handler) { }
    void addPlayer(Player *player) { _players.push_back(player); }

    void handle(const int delta_time) override {
        const auto mouse_position = static_cast<sf::Vector2f>(sf::Mouse::getPosition());
        for (auto *player : _players) {
            const bool is_moved = _key_handler->isKeyDown(player->getControl().move);
            player->setSpriteIndex(is_moved);
            if (is_moved) {
                auto *element = &player->getElement();
                _quadtree->remove(element);
                player->move(mouse_position, delta_time);
                _quadtree->insert(element);
            }
        }
    }
    
    ~PlayerExecutor() noexcept override {
        for (const auto *player : _players)
            delete player;
    }
    
    PlayerExecutor(PlayerExecutor&&) noexcept = default;
    PlayerExecutor& operator=(PlayerExecutor&&) noexcept = default;
        
    PlayerExecutor(const PlayerExecutor&) noexcept = delete;
    PlayerExecutor& operator=(const PlayerExecutor&) noexcept = delete;
};
