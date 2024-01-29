// ReSharper disable CppIncompleteSwitchStatement CppDefaultCaseNotHandledInSwitchStatement CppClangTidyCppcoreguidelinesProTypeStaticCastDowncast
#include "../../../../include/game/entity/services/EntityDamageImpactor.hpp"

EntityDamageImpactor::EntityDamageImpactor(EntityMaps& entity_maps, ElementCreator& element_creator,
                                           AnimationAttacher& animation_attacher, QuadtreeEl& quadtree, GameState &game_state):
    _entity_maps(&entity_maps), _dying_effect_animator(element_creator, animation_attacher),
    _quadtree(&quadtree), _game_state(&game_state) { }

void EntityDamageImpactor::removeFromQuadtree(const FightingEntity* fighting_entity) const {
    const Element* element = &fighting_entity->getGun().getElement();
    _quadtree->remove(element);
    delete element;

    element = &fighting_entity->getCharacter().getElement();
    _quadtree->remove(element);
    delete element;
}

void EntityDamageImpactor::removeFromQuadtree(const BulletCasing& bullet_casing) const {
    const auto* element = &bullet_casing.getElement();
    _quadtree->remove(element);
    delete element;
}

void EntityDamageImpactor::applyDamage(const BulletHarm& bullet_harm, Player* player) const {
    player->takeDamage(bullet_harm);

    if (player->isDead()) {
        _dying_effect_animator.createAnimation(*player);
        removeFromQuadtree(player);
        _entity_maps->fighting_maps.player_holder.removePlayer();
        *_game_state = GameState::LOSE;
    }
}

void EntityDamageImpactor::applyDamage(const BulletHarm& bullet_harm, Enemy* enemy) const {
    enemy->takeDamage(bullet_harm);

    if (enemy->isDead()) {
        _dying_effect_animator.createAnimation(*enemy);
        removeFromQuadtree(enemy);
        _entity_maps->fighting_maps.enemy_map.erase(enemy); 
    }
}

void EntityDamageImpactor::applyDamage(const BulletCasing& bullet_casing, Bullet* other_bullet) const {
    other_bullet->takeDamage(bullet_casing.getBulletHarm());

    if (other_bullet->isDead()) {
        _dying_effect_animator.createAnimation(*other_bullet, bullet_casing.getElement().getPolygon());
        removeFromQuadtree(other_bullet->getBulletCasing());
        _entity_maps->bullet_map.erase(other_bullet);
    }
}

void EntityDamageImpactor::applyDamage(const Bullet &bullet, const ElementCollisionSet &hits) const {
    for (const auto* hit : hits) {
        switch (const size_t id = hit->getId(); ElementIdTracker::extractType(id)) {
        case ElementType::CHARACTER: {
            const auto& enemy_map = _entity_maps->fighting_maps.enemy_map.getMap();
            if (const auto it_enemy = enemy_map.find(id); it_enemy != enemy_map.end())
                applyDamage(bullet.getBulletCasing().getBulletHarm(), it_enemy->second);
            else if (const auto& player = _entity_maps->fighting_maps.player_holder.getPlayer(); player->getId() == id)
                applyDamage(bullet.getBulletCasing().getBulletHarm(), player);
            break;
        }
        case ElementType::BULLET: {
            applyDamage(bullet.getBulletCasing(), _entity_maps->bullet_map.getMap().at(id));
            break;
        }
        }
    }
}

const DyingEffectAnimator& EntityDamageImpactor::getDyingAnimator() const{ return _dying_effect_animator; }