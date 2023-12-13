#pragma once

#include "WraithStats.hpp"
#include "../../EntityComponent.hpp"
#include "../../../../element/ReplaceableElement.hpp"

class Wraith final : public EntityComponent {
    ReplaceableElement* _element;
    WraithStats _wraith_stats;
public:
    Wraith(ReplaceableElement &element, const WraithStats &wraith_stats, const int num);
    [[nodiscard]] const WraithStats& getStats() const;
    [[nodiscard]] Element& getElement() const;
    void setSpriteIndex(const size_t sprite_index) const;
    
    ~Wraith() noexcept override = default;
    Wraith(Wraith&&) noexcept = default;
    Wraith& operator=(Wraith&&) noexcept = delete;
    Wraith(const Wraith&) noexcept = delete;
    Wraith& operator=(const Wraith&) noexcept = delete;
};
