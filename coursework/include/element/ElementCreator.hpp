#pragma once

#include "Element.hpp"
#include "ElementInfo.hpp"
#include "ReplaceableElement.hpp"
#include "../game/identifiable/ElementIdTracker.hpp"
#include "..\sprite\SpriteInfos.hpp"

class ElementCreator final {
    [[nodiscard]] SimpleSprite *createSprite(const ElementInfo &element_info);
    void fillSprites(ReplaceableSprites &sprites, const ElementInfo &element_info);

    SimpleSpriteInfos _simple_sprite_info;
    AnimatedSpriteInfos _animated_sprite_info;
    ElementIdTracker _id_tracker;

    static sf::Vector2f calcPoint0(const ElementInfo& element_info,  const sf::Vector2f& size, const sf::Vector2f& offset_factor);
public:
    static const sf::Vector2f NO_OFFSET_FACTOR;
    ElementCreator(const SimpleSpriteInfos& simple_sprite_info, const AnimatedSpriteInfos& animated_sprite_info);

    /**
     * Create an element with the specified properties.
     * @param element_info The info containing properties for the element (point - random point).
     * @param offset_factor Multiplier for the size vector to calculate point0 from the point specified in the element_info.
     * @return A pointer to the newly created Element.
     * @note Memory is allocated for the Element, and it is the caller's responsibility to free this memory.
     */
    [[nodiscard]] Element *create(const ElementInfo &element_info, const sf::Vector2f& offset_factor = NO_OFFSET_FACTOR);

    void setDefaultZIndex(const Element &element, const size_t num);
    
    /**
     * Create a replaceable element with the specified properties.
     * @param element_info The info containing properties for the replaceable element (point - random point).
     * @param offset_factor Multiplier for the size vector to calculate point0 from the point specified in the element_info.
     * @return A pointer to the newly created ReplaceableElement.
     * @note Memory is allocated for the ReplaceableElement, and it is the caller's responsibility to free this memory.
     */ 
    [[nodiscard]] ReplaceableElement *createReplaceable(const ElementInfo &element_info, const sf::Vector2f& offset_factor = NO_OFFSET_FACTOR);

    void loadTexture(const ElementType element_type, const size_t num);
    
    ~ElementCreator() noexcept = default;
    ElementCreator(const ElementCreator&) noexcept = delete;
    ElementCreator& operator=(const ElementCreator&) noexcept = delete;
    ElementCreator(ElementCreator&&) noexcept = delete;
    ElementCreator& operator=(ElementCreator&&) noexcept = delete;
};