#pragma once
#include "bullet/BulletMap.hpp"
#include "enemy/EnemyMap.hpp"

class EntityMaps final {
    Player *_player;
    BulletMap _bullet_map;
    EnemyMap _enemy_map;
public:
    explicit EntityMaps(Player *player): _player(player) {}
    
    [[nodiscard]] Player* const& getPlayer() const { return _player; }
    void removePlayer() { delete _player; _player = nullptr; }
    [[nodiscard]] BulletMap& getBulletMap() { return _bullet_map; }
    [[nodiscard]] EnemyMap& getEnemyMap() { return _enemy_map; }
    
    ~EntityMaps() noexcept { delete _player; } 
    EntityMaps(EntityMaps&&) noexcept = delete;
    EntityMaps& operator=(EntityMaps&&) noexcept = delete;
    EntityMaps(const EntityMaps&) noexcept = delete;
    EntityMaps& operator=(const EntityMaps&) noexcept = delete;
};