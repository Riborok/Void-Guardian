#pragma once
#include "CharacterStats.hpp"
#include "../EntityComponent.hpp"
#include "../../../../element/ReplaceableElement.hpp"

class Character final : public EntityComponent {
    ReplaceableElement* _element;
    CharacterStats _stats;
public:
    Character(ReplaceableElement &element, const CharacterStats &character_stats, const int num);
    [[nodiscard]] const CharacterStats& getStats() const;
    [[nodiscard]] Element& getElement() const;
    void setSpriteIndex(const size_t sprite_index) const;
    
    ~Character() noexcept override = default;
    Character(Character&&) noexcept = default;
    Character& operator=(Character&&) noexcept = delete;
    Character(const Character&) noexcept = delete;
    Character& operator=(const Character&) noexcept = delete;
};
