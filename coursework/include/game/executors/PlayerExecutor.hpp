#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

#include "../../additionally/QuadtreeEl.hpp"
#include "../../additionally/Types.hpp"
#include "../input/KeyHandler.hpp"
#include "../player/Player.hpp"

class PlayerExecutor final : public Executor {
    sf::RenderWindow *_window;
    KeyHandler *_key_handler;
    std::vector<Player*> _players;
    QuadtreeEl *_quadtree;
public:
    PlayerExecutor(sf::RenderWindow &window, KeyHandler& key_handler, QuadtreeEl& quadtree);

    void addPlayer(Player* player);

    void handle(const int delta_time) override;

    ~PlayerExecutor() noexcept override;
    
    PlayerExecutor(PlayerExecutor&&) noexcept = default;
    PlayerExecutor& operator=(PlayerExecutor&&) noexcept = default;
        
    PlayerExecutor(const PlayerExecutor&) noexcept = delete;
    PlayerExecutor& operator=(const PlayerExecutor&) noexcept = delete;
};