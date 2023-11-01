﻿#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Mouse.hpp>

#include "../../additionally/Types.h"
#include "../input/KeyHandler.h"
#include "../player/Player.h"

class PlayerExecutor final : public Types::Executor {
    sf::RenderWindow *_window;
    KeyHandler *_key_handler;
    std::vector<Player*> _players;
public:
    PlayerExecutor(sf::RenderWindow &window, KeyHandler &key_handler) : _window(&window), _key_handler(&key_handler) { }
    void addPlayer(Player *player) { _players.push_back(player); }

    void handle(const int delta_time) override {
        for (auto *player : _players) {
            const bool is_moved = _key_handler->isKeyDown(player->getControl().move);
            player->setSpriteIndex(is_moved);
            if (is_moved)
                player->move(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*_window)), _window->getSize(), delta_time);
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