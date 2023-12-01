#pragma once

#include "Element.hpp"
#include "ElementData.hpp"
#include "ReplaceableElement.hpp"
#include "../game/identifiable/ElementIdTracker.hpp"

class ElementCreator final {
    [[nodiscard]] SimpleSprite *createSprite(const ElementData &element_data) const;
    void fillSprites(ReplaceableSprites &sprites, const ElementData &element_data) const;

    SimpleSpriteInfos _simple_sprite_info;
    AnimatedSpriteInfos _animated_sprite_info;
    ElementIdTracker _id_tracker;
public:
    ElementCreator(SimpleSpriteInfos &&simple_sprite_info, AnimatedSpriteInfos &&animated_sprite_info);
    
    /**
     * Create an element with the specified properties.
     * @param element_data The data containing properties for the element.
     * @param origin The origin vector indicating the initial position of the element's sprite (default: {0, 0}).
     * @return A pointer to the newly created Element.
     * @note Memory is allocated for the Element, and it is the caller's responsibility to free this memory.
     */
    [[nodiscard]] Element *create(const ElementData &element_data, const sf::Vector2f &origin = {0, 0});

    /**
     * Create a replaceable element with the specified properties.
     * @param element_data The data containing properties for the replaceable element.
     * @param origin The origin vector indicating the initial position of the element's sprite (default: {0, 0}).
     * @return A pointer to the newly created ReplaceableElement.
     * @note Memory is allocated for the ReplaceableElement, and it is the caller's responsibility to free this memory.
     */
    [[nodiscard]] ReplaceableElement *createReplaceable(const ElementData &element_data, const sf::Vector2f &origin = {0, 0});
    
    ~ElementCreator() noexcept = default;
    ElementCreator(const ElementCreator&) noexcept = delete;
    ElementCreator& operator=(const ElementCreator&) noexcept = delete;
    ElementCreator(ElementCreator&&) noexcept = delete;
    ElementCreator& operator=(ElementCreator&&) noexcept = delete;
};
