#include "../../../../include/game/entity/services/EntityCreator.hpp"

#include "../../../../include/geometry/GeomAuxiliaryFunc.hpp"

EntityCreator::EntityCreator(ElementCreator &element_creator, const EntityInfoTables& entity_info_tables) :
    _element_creator(&element_creator), _entity_info_tables(entity_info_tables){ }

Gun EntityCreator::createGun(const sf::Vector2f& p, const float angle, const size_t num) const {
    const auto &info = _entity_info_tables.gun_infos[num].data;
    const auto &scale = _entity_info_tables.gun_infos[num].scale;
    
    return {*_element_creator->create({p, angle, ElementType::GUN, num, scale}),
        info, num};
}

Character EntityCreator::createCharacter(const sf::Vector2f& p, const float angle, const size_t num, const sf::Vector2f& offset_factor) const {
    const auto &info = _entity_info_tables.character_infos[num].data;
    const auto &scale = _entity_info_tables.character_infos[num].scale;
    
    return {
        *_element_creator->createReplaceable({p, angle, ElementType::CHARACTER, num, scale}, offset_factor),
        info,
        num
    };
}

Gun EntityCreator::createGun(const sf::Vector2f& p, const float angle, const size_t num, const sf::Vector2f& offset_factor) const {
    const auto &info = _entity_info_tables.gun_infos[num].data;
    const auto &scale = _entity_info_tables.gun_infos[num].scale;
    
    return {*_element_creator->create({p, angle, ElementType::GUN, num, scale}, offset_factor),
        info, num};
}

Player* EntityCreator::createPlayer(const FightingEntityInfo &player_info, const Control &control, const sf::Vector2f& offset_factor) const {
    const auto &info = _entity_info_tables.character_infos[player_info.character_num].entity_info;
    
    auto character = createCharacter(player_info.pos, player_info.angle, player_info.character_num, offset_factor);
    const auto center(character.getElement().getPolygon().calcCenter());
    return new Player(
        std::move(character),
        createGun(center, player_info.angle, player_info.gun_num),
        info, control
    );
}

Enemy* EntityCreator::createEnemy(const FightingEntityInfo& player_info, const sf::Vector2f& offset_factor) const {
    const auto &info = _entity_info_tables.character_infos[player_info.character_num].entity_info;
    
    auto character = createCharacter(player_info.pos, player_info.angle, player_info.character_num, offset_factor);
    const auto center(character.getElement().getPolygon().calcCenter());
    return new Enemy(
        std::move(character),
        createGun(center, player_info.angle, player_info.gun_num),
        info
    );
}

Bullet* EntityCreator::createBullet(const LaunchData &launch_data) const {
    const auto &info = _entity_info_tables.bullet_infos[launch_data.num];

    const BulletInfo bullet_info = info.data * launch_data.bullet_multipliers;
    sf::Vector2f velocity = launch_data.velocity; GeomAuxiliaryFunc::setLength(velocity, bullet_info.speed);
    return new Bullet(
        {*_element_creator->create({launch_data.point, launch_data.angle,
            ElementType::BULLET, launch_data.num, info.scale}), bullet_info.bullet_stats, launch_data.num},
        velocity,
        info.entity_info
    );
}

void EntityCreator::setDefaultZIndex(const Element &element, const size_t num) const {
    _element_creator->setDefaultZIndex(element, num);
}