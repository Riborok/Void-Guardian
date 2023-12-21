#pragma once
#include "BulletStats.hpp"
#include "../EntityComponent.hpp"
#include "../../../../element/Element.hpp"

class BulletCasing final : public EntityComponent{
    Element *_element;
    BulletStats _stats;
public:
    BulletCasing(Element &element, const BulletStats &stats, const size_t num);
    [[nodiscard]] const BulletStats &getStats() const;
    [[nodiscard]] const Element& getElement() const;
    void move(const sf::Vector2f &velocity) const;
    
    ~BulletCasing() noexcept override = default;
    BulletCasing(BulletCasing&&) noexcept = default;
    BulletCasing& operator=(BulletCasing&&) noexcept = delete;
    BulletCasing(const BulletCasing&) noexcept = delete;
    BulletCasing& operator=(const BulletCasing&) noexcept = delete;
};
