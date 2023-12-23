#pragma once
#include "EnemySpawnConfiguration.hpp"

enum class EnemySpawnResult final {
    WAITING = 0,
    SPAWN,
    FINISH,
};

class EnemySpawnSettings final {
    EnemySpawnConfiguration _target_configuration;  
    EnemySpawnConfiguration _current_configuration;
public:
    explicit EnemySpawnSettings(const EnemySpawnConfiguration &target_configuration) noexcept:
        _target_configuration(target_configuration), _current_configuration() { }
    void markFailedSpawn() { --_current_configuration.enemies_amount; }
    EnemySpawnResult getEnemySpawnResult(const int delta_time) {
        _current_configuration.spawn_interval += delta_time;
        if (_current_configuration.spawn_interval >= _target_configuration.spawn_interval) {
            _current_configuration.spawn_interval -= _target_configuration.spawn_interval;
            if (_current_configuration.enemies_amount >= _target_configuration.enemies_amount) {
                _current_configuration = {};
                return EnemySpawnResult::FINISH;
            }
            ++_current_configuration.enemies_amount;
            return EnemySpawnResult::SPAWN;
        }
        return EnemySpawnResult::WAITING;
    }
    
    ~EnemySpawnSettings() noexcept = default;
    EnemySpawnSettings(EnemySpawnSettings&&) noexcept = delete;
    EnemySpawnSettings& operator=(EnemySpawnSettings&&) noexcept = delete;
    EnemySpawnSettings(const EnemySpawnSettings&) noexcept = delete;
    EnemySpawnSettings& operator=(const EnemySpawnSettings&) noexcept = delete;
};