#pragma once

#include "../../additionally/Types.hpp"
#include "../../Quadtree/Quadtree.hpp"
#include "../input/KeyHandler.hpp"
#include "../player/Player.hpp"

class PlayerExecutor final : public Types::Executor {
    Quadtree<Element> *_quadtree;
    KeyHandler *_key_handler;
    std::vector<Player*> _players;
public:
    PlayerExecutor(Quadtree<Element>& quadtree, KeyHandler& key_handler);

    void addPlayer(Player* player);

    void handle(const int delta_time) override;

    ~PlayerExecutor() noexcept override;
    
    PlayerExecutor(PlayerExecutor&&) noexcept = default;
    PlayerExecutor& operator=(PlayerExecutor&&) noexcept = default;
        
    PlayerExecutor(const PlayerExecutor&) noexcept = delete;
    PlayerExecutor& operator=(const PlayerExecutor&) noexcept = delete;
};