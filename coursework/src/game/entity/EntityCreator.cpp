#include "../../../include/game/entity/EntityCreator.hpp"

EntityCreator::EntityCreator(ElementCreator &element_creator, const WraithInfos& wraith_infos,
              const GunInfos& gun_infos, const BulletInfos& bullet_infos) :
    _element_creator(&element_creator), _wraith_infos(wraith_infos),
    _gun_infos(gun_infos), _bullet_infos(bullet_infos) { }

Gun EntityCreator::createGun(const sf::Vector2f& p, const float angle, const int num) const {
    const auto &info = _gun_infos[num].data;
    const auto &scale = _gun_infos[num].scale;
    
    return {*_element_creator->create({p, angle, ElementType::GUN, num, scale}),
        info, num};
}

Wraith EntityCreator::createWraith(const sf::Vector2f& p, const float angle, const int num, const sf::Vector2f& offset_factor) const {
    const auto &info = _wraith_infos[num].data;
    const auto &scale = _wraith_infos[num].scale;
    
    return {
        *_element_creator->createReplaceable({p, angle, ElementType::WRAITH, num, scale}, offset_factor),
        info,
        num
    };
}

Gun EntityCreator::createGun(const sf::Vector2f& p, const float angle, const int num, const sf::Vector2f& offset_factor) const {
    const auto &info = _gun_infos[num].data;
    const auto &scale = _gun_infos[num].scale;
    
    return {*_element_creator->create({p, angle, ElementType::GUN, num, scale}, offset_factor),
        info, num};
}

Player* EntityCreator::createPlayer(const PlayerInfo &player_info, const sf::Vector2f& offset_factor) const {
    const auto &info = _wraith_infos[player_info.wraith_num].entity_info;
    
    auto wraith = createWraith(player_info.pos, player_info.angle, player_info.wraith_num, offset_factor);
    const auto center(wraith.getElement().getPolygon().calcCenter());
    return new Player(
        std::move(wraith),
        createGun(center, player_info.angle, player_info.gun_num),
        info
    );
}

Bullet* EntityCreator::createBullet(const LaunchData &launch_data) const {
    const auto &info = _bullet_infos[launch_data.num];

    return new Bullet(
        *_element_creator->create({launch_data.point, launch_data.angle,
            ElementType::BULLET, launch_data.num, info.scale}),
        launch_data.velocity,
        info.data * launch_data.bullet_multipliers,
        info.entity_info,
        launch_data.num
    );
}

void EntityCreator::setDefaultZIndex(const Element &element, const int num) const {
    _element_creator->setDefaultZIndex(element, num);
}