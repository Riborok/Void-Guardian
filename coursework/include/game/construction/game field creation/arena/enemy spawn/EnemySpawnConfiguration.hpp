#pragma once

struct EnemySpawnConfiguration final {
    size_t enemies_amount;
    int spawn_interval;
    EnemySpawnConfiguration(const size_t enemies_amount, const int spawn_interval):
        enemies_amount(enemies_amount), spawn_interval(spawn_interval){}
    EnemySpawnConfiguration(): enemies_amount(0), spawn_interval(0){}
};