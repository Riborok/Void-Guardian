#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Mouse.hpp>

#include "../../additionally/Types.h"
#include "../input/KeyHandler.h"
#include "../player/Player.h"

class PlayerManager final : public Types::Executor {
    sf::RenderWindow *_window;
    KeyHandler *_key_handler;
    std::vector<Player*> _players;
public:
    PlayerManager(sf::RenderWindow &window, KeyHandler &key_handler) : _window(&window), _key_handler(&key_handler) { }
    void addPlayer(Player *player) { _players.push_back(player); }

    void handle(const int delta_time) override {
        for (auto *player : _players)
            if (_key_handler->isKeyDown(player->getControl().move))
                player->move(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*_window)), _window->getSize(), delta_time);
    }
    
    ~PlayerManager() noexcept override {
        for (const auto *player : _players)
            delete player;
    }
    
    PlayerManager(PlayerManager&&) noexcept = default;
    PlayerManager& operator=(PlayerManager&&) noexcept = default;
        
    PlayerManager(const PlayerManager&) noexcept = delete;
    PlayerManager& operator=(const PlayerManager&) noexcept = delete;
};
