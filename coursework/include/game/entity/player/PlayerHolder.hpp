#pragma once
#include "Player.hpp"

class PlayerHolder final {
    Player *_player;
public:
    explicit PlayerHolder(Player *player): _player(player) {}
    [[nodiscard]] Player* const& getPlayer() const { return _player; }
    void removePlayer() { delete _player; _player = nullptr; }
    
    ~PlayerHolder() noexcept { delete _player; } 
    PlayerHolder(PlayerHolder&& player_holder) noexcept : _player(player_holder._player) { player_holder._player = nullptr; }
    PlayerHolder& operator=(PlayerHolder&&) noexcept = delete;
    PlayerHolder(const PlayerHolder&) noexcept = delete;
    PlayerHolder& operator=(const PlayerHolder&) noexcept = delete;
};