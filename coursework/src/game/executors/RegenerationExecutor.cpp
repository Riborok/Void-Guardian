#include "../../../include/game/executors/RegenerationExecutor.hpp"

RegenerationExecutor::RegenerationExecutor(FightingMaps& fighting_maps): _fighting_maps(&fighting_maps) {}

void RegenerationExecutor::handle(const int delta_time) {
    if (_fighting_maps->player_holder.getPlayer())
        _fighting_maps->player_holder.getPlayer()->updateTimeWithoutDamage(delta_time);
    for (const auto [id, enemy] : _fighting_maps->enemy_map.getMap())
        enemy->updateTimeWithoutDamage(delta_time);
}