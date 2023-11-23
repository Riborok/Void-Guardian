#pragma once

#include "Element.hpp"
#include "ReplaceableElement.hpp"
#include "../additionally/other types/InitializationData.hpp"
#include "../game/identifiable/ElementIdTracker.hpp"

class ElementCreator final {
    [[nodiscard]] SimpleSprite* createSprite(const ElementData &element_data) const;
    void fillSprites(ReplaceableSprites &sprites, const ElementData &element_data) const;

    SimpleSpriteInfos _simple_sprite_info;
    AnimatedSpriteInfos _animated_sprite_info;
    ElementIdTracker _id_tracker;
public:
    ElementCreator(SimpleSpriteInfos &&simple_sprite_info, AnimatedSpriteInfos &&animated_sprite_info);
    
    /**
     * Create an element with the specified properties.
     * @param element_data The data containing properties for the element.
     * @return A pointer to the newly created Element.
     * @note Memory is allocated for the Element, and it is the caller's responsibility to free this memory.
     */
    [[nodiscard]] Element *create(const ElementData &element_data);

    /**
     * Create a replaceable element with the specified properties.
     * @param element_data The data containing properties for the replaceable element.
     * @return A pointer to the newly created ReplaceableElement.
     * @note Memory is allocated for the ReplaceableElement, and it is the caller's responsibility to free this memory.
     */
    [[nodiscard]] ReplaceableElement *createReplaceable(const ElementData &element_data);
    
    ~ElementCreator() noexcept = default;
    ElementCreator(const ElementCreator&) noexcept = delete;
    ElementCreator& operator=(const ElementCreator&) noexcept = delete;
    ElementCreator(ElementCreator&&) noexcept = delete;
    ElementCreator& operator=(ElementCreator&&) noexcept = delete;
};
