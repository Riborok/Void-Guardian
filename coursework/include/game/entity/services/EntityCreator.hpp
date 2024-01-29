#pragma once
#include "../FightingEntityInfo.hpp"
#include "../InfoTables.hpp"
#include "../../../element/ElementCreator.hpp"
#include "../bullet/Bullet.hpp"
#include "../enemy/Enemy.hpp"
#include "../player/Player.hpp"

class EntityCreator final {
    ElementCreator *_element_creator;
    EntityInfoTables _entity_info_tables;

    [[nodiscard]] sf::Vector2f getGunPos(const sf::Vector2f &pos, const sf::Vector2f &gun_offset, const size_t gun_num) const;
    [[nodiscard]] Character createCharacter(const sf::Vector2f& p, const float angle, const size_t num, const sf::Vector2f& offset_factor) const;
public:
    EntityCreator(ElementCreator &element_creator, const EntityInfoTables& entity_info_tables);
    void setDefaultZIndex(const Element &element, const size_t num) const;
    
    [[nodiscard]] Gun createGun(const sf::Vector2f& p, const float angle, const size_t num,
        const sf::Vector2f& offset_factor = ElementCreator::NO_OFFSET_FACTOR) const;
    [[nodiscard]] Player* createPlayer(const FightingEntityInfo &player_info, const Control &control,
        const sf::Vector2f& offset_factor = ElementCreator::NO_OFFSET_FACTOR) const;
    [[nodiscard]] Enemy* createEnemy(const FightingEntityInfo &enemy_info, 
        const sf::Vector2f& offset_factor = ElementCreator::NO_OFFSET_FACTOR) const;
    [[nodiscard]] Bullet* createBullet(const LaunchInfo &launch_info) const;
    
    ~EntityCreator() noexcept = default;
    EntityCreator(const EntityCreator&) noexcept = delete;
    EntityCreator& operator=(const EntityCreator&) noexcept = delete;
    EntityCreator(EntityCreator&&) noexcept = delete;
    EntityCreator& operator=(EntityCreator&&) noexcept = delete;
};
