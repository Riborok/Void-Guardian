#pragma once
#include "Gun.hpp"
#include "../../services/EntityCreator.hpp"
#include "../../../../geometry/collision/CollisionHandler.hpp"
#include "../../../../quadtree/quadtree type defs/QuadtreeEl.hpp"

class GunInstaller final {
    static constexpr float LEAN = -0.785f;
    typedef std::unordered_map<size_t, Gun> Guns;
    const sf::Vector2f _offset_factor{-0.5f, -0.5f};
    
    const EntityCreator *_entity_creator;
    const CollisionHandler *_collision_handler;
    QuadtreeEl *_quadtree;
    Guns _guns;
    static void setAngle(Element &element);
    void setWeaponSettings(const Gun &gun) const;
public:
    GunInstaller(const EntityCreator &entity_creator, const CollisionHandler &collision_handler, QuadtreeEl &quadtree);
    void createGun(const sf::Vector2f& p, const size_t num);
    void swapGuns(Player &player, const Element &gun);
    
    ~GunInstaller() noexcept = default;
    GunInstaller(GunInstaller&&) noexcept = default;
    GunInstaller& operator=(GunInstaller&&) noexcept = delete;
    GunInstaller(const GunInstaller&) noexcept = delete;
    GunInstaller& operator=(const GunInstaller&) noexcept = delete;
};