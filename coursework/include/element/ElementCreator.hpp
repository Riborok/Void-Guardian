#pragma once

#include "Element.hpp"
#include "ElementData.hpp"
#include "ReplaceableElement.hpp"
#include "../game/identifiable/ElementIdTracker.hpp"
#include "../sprite/Infos.hpp"

class ElementCreator final {
    [[nodiscard]] SimpleSprite *createSprite(const ElementData &element_data);
    void fillSprites(ReplaceableSprites &sprites, const ElementData &element_data);

    SimpleSpriteInfos _simple_sprite_info;
    AnimatedSpriteInfos _animated_sprite_info;
    ElementIdTracker _id_tracker;

    static sf::Vector2f calcPoint0(const ElementData& element_data,  const sf::Vector2f& size, const sf::Vector2f& size_factor);
public:
    ElementCreator(SimpleSpriteInfos &&simple_sprite_info, AnimatedSpriteInfos &&animated_sprite_info);
    
    /**
     * Create an element with the specified properties.
     * @param element_data The data containing properties for the element (point - the points[0] of the polygon).
     * @return A pointer to the newly created Element.
     * @note Memory is allocated for the Element, and it is the caller's responsibility to free this memory.
     */
    [[nodiscard]] Element *create(const ElementData &element_data);

    /**
     * Create an element with the specified properties.
     * @param element_data The data containing properties for the element (point - random point).
     * @param size_factor Multiplier for the size vector to calculate point0 from the point specified in the element_data.
     * @return A pointer to the newly created Element.
     * @note Memory is allocated for the Element, and it is the caller's responsibility to free this memory.
     */
    [[nodiscard]] Element *create(const ElementData &element_data, const sf::Vector2f& size_factor);

    /**
     * Create a replaceable element with the specified properties.
     * @param element_data The data containing properties for the replaceable element (point - the points[0] of the polygon).
     * @return A pointer to the newly created ReplaceableElement.
     * @note Memory is allocated for the ReplaceableElement, and it is the caller's responsibility to free this memory.
     */
    [[nodiscard]] ReplaceableElement *createReplaceable(const ElementData &element_data);

    /**
     * Create a replaceable element with the specified properties.
     * @param element_data The data containing properties for the replaceable element (point - random point).
     * @param size_factor Multiplier for the size vector to calculate point0 from the point specified in the element_data.
     * @return A pointer to the newly created ReplaceableElement.
     * @note Memory is allocated for the ReplaceableElement, and it is the caller's responsibility to free this memory.
     */ 
    [[nodiscard]] Element *createReplaceable(const ElementData &element_data, const sf::Vector2f& size_factor);
    
    ~ElementCreator() noexcept = default;
    ElementCreator(const ElementCreator&) noexcept = delete;
    ElementCreator& operator=(const ElementCreator&) noexcept = delete;
    ElementCreator(ElementCreator&&) noexcept = delete;
    ElementCreator& operator=(ElementCreator&&) noexcept = delete;
};
