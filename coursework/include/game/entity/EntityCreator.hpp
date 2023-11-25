#pragma once
#include "InfoTables.hpp"
#include "../../element/ElementCreator.hpp"
#include "player/Player.hpp"

class EntityCreator final {
    ElementCreator *_element_creator;
    WraithInfos _wraith_infos;
    GunInfos _gun_infos;
    BulletInfos _bullet_infos;

    [[nodiscard]] Gun createGun(const sf::Vector2f& p, const float angle, const int num) const;
    [[nodiscard]] Wraith createWraith(const sf::Vector2f& p, const float angle, const int num) const;
public:
    EntityCreator(ElementCreator &element_creator, const WraithInfos& wraith_infos,
                  const GunInfos& gun_infos, const BulletInfos& bullet_infos);

    [[nodiscard]] Player* createPlayer(const sf::Vector2f& p, const float angle, const int num, const int gun_num) const;
    
    ~EntityCreator() noexcept = default;
    EntityCreator(const EntityCreator&) noexcept = delete;
    EntityCreator& operator=(const EntityCreator&) noexcept = delete;
    EntityCreator(EntityCreator&&) noexcept = delete;
    EntityCreator& operator=(EntityCreator&&) noexcept = delete;
};
