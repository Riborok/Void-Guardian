#pragma once
#include "../../EntityCreator.hpp"
#include "../../../../quadtree/quadtree type defs/QuadtreeEl.hpp"

class GunManager final {
    static const sf::Vector2f OFFSET_FACTOR;
    static constexpr float LEAN = -0.785f;
    typedef std::unordered_map<size_t, Gun> Guns;
    
    const EntityCreator *_entity_creator;
    QuadtreeEl *_quadtree;
    Guns _guns;
    void setWeaponSettings(const Gun &gun) const;
public:
    GunManager(const EntityCreator &entity_creator, QuadtreeEl &quadtree);
    void createGun(const sf::Vector2f& p, const int num);
    void swapGuns(Player &player, const Element &gun);
    
    ~GunManager() noexcept = default;
    GunManager(GunManager&&) noexcept = default;
    GunManager& operator=(GunManager&&) noexcept = default;
    GunManager(const GunManager&) noexcept = delete;
    GunManager& operator=(const GunManager&) noexcept = delete;
};