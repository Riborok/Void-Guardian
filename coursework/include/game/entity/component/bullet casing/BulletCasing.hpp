#pragma once
#include "BulletHarm.hpp"
#include "../EntityComponent.hpp"
#include "../../../../element/Element.hpp"

class BulletCasing final : public EntityComponent{
    Element *_element;
    BulletHarm _bullet_harm;
public:
    BulletCasing(Element &element, const BulletHarm &bullet_harm, const size_t num);
    [[nodiscard]] const BulletHarm &getBulletHarm() const;
    [[nodiscard]] const Element& getElement() const;
    void move(const sf::Vector2f &velocity) const;
    
    ~BulletCasing() noexcept override = default;
    BulletCasing(BulletCasing&&) noexcept = default;
    BulletCasing& operator=(BulletCasing&&) noexcept = delete;
    BulletCasing(const BulletCasing&) noexcept = delete;
    BulletCasing& operator=(const BulletCasing&) noexcept = delete;
};
