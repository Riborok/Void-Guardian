#include "../../../include/game/executors/BulletExecutor.hpp"

BulletExecutor::BulletExecutor(CollisionManager &collision_manager, BulletMap &bullet_map,
        EntityDeathManager &&entity_death_manager):
    _collision_manager(&collision_manager), _bullet_map(&bullet_map),
    _entity_death_manager(std::move(entity_death_manager)) { }

void BulletExecutor::handle(const int delta_time) {
    
}