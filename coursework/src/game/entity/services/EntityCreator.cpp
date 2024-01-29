#include "../../../../include/game/entity/services/EntityCreator.hpp"

#include "../../../../include/geometry/GeomAuxiliaryFunc.hpp"

EntityCreator::EntityCreator(ElementCreator &element_creator, const EntityInfoTables& entity_info_tables) :
    _element_creator(&element_creator), _entity_info_tables(entity_info_tables){ }

sf::Vector2f EntityCreator::getGunPos(const sf::Vector2f &pos, const sf::Vector2f &gun_offset, const size_t gun_num) const {
    const sf::Vector2f &owner_center_offset = _entity_info_tables.gun_infos[gun_num].info.gun_properties.owner_center_offset;
    return {pos.x + gun_offset.x + owner_center_offset.x, pos.y + gun_offset.y + owner_center_offset.y};
}

Character EntityCreator::createCharacter(const sf::Vector2f& p, const float angle, const size_t num, const sf::Vector2f& offset_factor) const {
    const auto &info = _entity_info_tables.character_infos[num];
    return {
        *_element_creator->createReplaceable({p, angle, ElementType::CHARACTER, num, info.scale},
            offset_factor), info.info, num
    };
}

Gun EntityCreator::createGun(const sf::Vector2f& p, const float angle, const size_t num, const sf::Vector2f& offset_factor) const {
    const auto &info = _entity_info_tables.gun_infos[num];
    return {
        *_element_creator->create({p, angle, ElementType::GUN, num, info.scale}, offset_factor),
        info.info, num
    };
}

Player* EntityCreator::createPlayer(const FightingEntityInfo &player_info, const Control &control, const sf::Vector2f& offset_factor) const {
    const auto &info = _entity_info_tables.character_infos[player_info.character_num];
    auto character(createCharacter(player_info.pos, player_info.angle, player_info.character_num, offset_factor));
    const auto center(character.getElement().getPolygon().calcCenter());
    return new Player(
        std::move(character),
        createGun(getGunPos(center, info.gun_offset, player_info.gun_num), player_info.angle, player_info.gun_num),
        info.entity_info, info.gun_offset, control
    );
}

Enemy* EntityCreator::createEnemy(const FightingEntityInfo& enemy_info, const sf::Vector2f& offset_factor) const {
    const auto &info = _entity_info_tables.character_infos[enemy_info.character_num];
    auto character(createCharacter(enemy_info.pos, enemy_info.angle, enemy_info.character_num, offset_factor));
    const auto center(character.getElement().getPolygon().calcCenter());
    return new Enemy(
        std::move(character),
        createGun(getGunPos(center, info.gun_offset, enemy_info.gun_num), enemy_info.angle, enemy_info.gun_num),
        info.entity_info, info.gun_offset
    );
}

Bullet* EntityCreator::createBullet(const LaunchInfo &launch_info) const {
    const auto &info = _entity_info_tables.bullet_infos[launch_info.num];

    const BulletStats bullet_stats = info.info * launch_info.bullet_multipliers;
    sf::Vector2f velocity = launch_info.velocity; GeomAuxiliaryFunc::setLength(velocity, bullet_stats.speed);
    return new Bullet(
        {*_element_creator->create({launch_info.point, launch_info.angle,
            ElementType::BULLET, launch_info.num, info.scale}), bullet_stats.bullet_harm, launch_info.num},
        velocity,
        info.entity_info
    );
}

void EntityCreator::setDefaultZIndex(const Element &element, const size_t num) const {
    _element_creator->setDefaultZIndex(element, num);
}