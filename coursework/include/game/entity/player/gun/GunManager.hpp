#pragma once
#include "../../EntityCreator.hpp"
#include "../../../../geometry/collision/CollisionManager.hpp"
#include "../../../../quadtree/quadtree type defs/QuadtreeEl.hpp"

class GunManager final {
    static constexpr float LEAN = -0.785f;
    typedef std::unordered_map<size_t, Gun> Guns;
    const sf::Vector2f _offset_factor{-0.5f, -0.5f};
    
    const EntityCreator *_entity_creator;
    const CollisionManager *_collision_manager;
    QuadtreeEl *_quadtree;
    Guns _guns;
    static void setAngle(Element &element);
    void processCollisions(const Element &element) const;
    void setWeaponSettings(const Gun &gun) const;
public:
    GunManager(const EntityCreator &entity_creator, const CollisionManager &collision_manager, QuadtreeEl &quadtree);
    void createGun(const sf::Vector2f& p, const int num);
    void swapGuns(Player &player, const Element &gun);
    
    ~GunManager() noexcept = default;
    GunManager(GunManager&&) noexcept = default;
    GunManager& operator=(GunManager&&) noexcept = delete;
    GunManager(const GunManager&) noexcept = delete;
    GunManager& operator=(const GunManager&) noexcept = delete;
};