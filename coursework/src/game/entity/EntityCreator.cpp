#include "../../../include/game/entity/EntityCreator.hpp"

EntityCreator::EntityCreator(ElementCreator &element_creator, const WraithInfos& wraith_infos,
              const GunInfos& gun_infos, const BulletInfos& bullet_infos) :
    _element_creator(&element_creator), _wraith_infos(wraith_infos),
    _gun_infos(gun_infos), _bullet_infos(bullet_infos) { }

Gun EntityCreator::createGun(const sf::Vector2f& p, const float angle, const int num) const {
    const auto &info = _gun_infos[num];
    return {
        *_element_creator->create({p, angle, ElementType::GUN, num, info.scale}),
        info.info};
}

Wraith EntityCreator::createWraith(const sf::Vector2f& p, const float angle, const int num) const {
    const auto &info = _wraith_infos[num].info;
    const auto &scale = _wraith_infos[num].scale;
    
    return {
        *_element_creator->createReplaceable({p, angle, ElementType::WRAITH, num, scale}),
        info
    };
}

Player* EntityCreator::createPlayer(const sf::Vector2f& p, const float angle, const int num, const int gun_num) const {
    const auto &info = _wraith_infos[num].entity_info;
    
    auto wraith = createWraith(p, angle, num);
    const auto center(wraith.getElement().getPolygon().calcCenter());
    return new Player(
        std::move(wraith),
        createGun(center, angle, gun_num),
        info
    );
}
