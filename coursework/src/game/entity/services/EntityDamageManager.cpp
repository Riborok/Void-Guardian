// ReSharper disable CppIncompleteSwitchStatement CppDefaultCaseNotHandledInSwitchStatement CppClangTidyCppcoreguidelinesProTypeStaticCastDowncast
#include "../../../../include/game/entity/services/EntityDamageManager.hpp"

EntityDamageManager::EntityDamageManager(EntityMaps& entity_maps, ElementCreator& element_creator,
    AnimationManager& animation_manager, QuadtreeEl& quadtree, GameState &game_state):
    _entity_maps(&entity_maps), _dying_effect_animator(element_creator, animation_manager),
    _quadtree(&quadtree), _game_state(&game_state) { }

void EntityDamageManager::removeFromQuadtree(const FightingEntity* fighting_entity) const {
    const Element* element = &fighting_entity->getGun().getElement();
    _quadtree->remove(element);
    delete element;

    element = &fighting_entity->getCharacter().getElement();
    _quadtree->remove(element);
    delete element;
}

void EntityDamageManager::removeFromQuadtree(const BulletCasing& bullet_casing) const {
    const auto* element = &bullet_casing.getElement();
    _quadtree->remove(element);
    delete element;
}

void EntityDamageManager::applyDamage(const BulletStats& bullet_stats, Player* player) const {
    player->takeDamage(bullet_stats);

    if (player->isDead()) {
        _dying_effect_animator.createAnimation(*player);
        removeFromQuadtree(player);
        _entity_maps->player_holder.removePlayer();
        *_game_state = GameState::LOSE;
    }
}

void EntityDamageManager::applyDamage(const BulletStats& bullet_stats, Enemy* enemy) const {
    enemy->takeDamage(bullet_stats);

    if (enemy->isDead()) {
        _dying_effect_animator.createAnimation(*enemy);
        removeFromQuadtree(enemy);
        _entity_maps->enemy_map.erase(enemy); 
    }
}

void EntityDamageManager::applyDamage(const BulletCasing& bullet_casing, Bullet* other_bullet) const {
    other_bullet->takeDamage(bullet_casing.getStats());

    if (other_bullet->isDead()) {
        _dying_effect_animator.createAnimation(*other_bullet, bullet_casing.getElement().getPolygon());
        removeFromQuadtree(other_bullet->getBulletCasing());
        _entity_maps->bullet_map.erase(other_bullet);
    }
}

void EntityDamageManager::applyDamage(const Bullet &bullet, const ElementCollisionSet &hits) const {
    for (const auto* hit : hits) {
        switch (const size_t id = hit->getId(); ElementIdTracker::extractType(id)) {
        case ElementType::CHARACTER: {
            const auto& enemy_map = _entity_maps->enemy_map.getMap();
            if (const auto it_enemy = enemy_map.find(id); it_enemy != enemy_map.end())
                applyDamage(bullet.getBulletCasing().getStats(), it_enemy->second);
            else if (const auto& player = _entity_maps->player_holder.getPlayer(); player->getId() == id)
                applyDamage(bullet.getBulletCasing().getStats(), player);
            break;
        }
        case ElementType::BULLET: {
            applyDamage(bullet.getBulletCasing(), _entity_maps->bullet_map.getMap().at(id));
            break;
        }
        }
    }
}

const DyingEffectAnimator& EntityDamageManager::getDyingAnimator() const{ return _dying_effect_animator; }