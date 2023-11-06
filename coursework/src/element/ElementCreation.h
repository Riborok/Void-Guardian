#pragma once
#include <string>

#include "Element.h"
#include "ReplaceableElement.h"
#include "../additionally/Constants.h"
#include "../additionally/Types.h"
#include "../game/identifiable/IdTracker.h"
#include "../model/polygon/Rectangle.h"
#include "../sprite/AnimatedSprite.h"
#include "../sprite/SimpleSprite.h"

namespace ElementCreation {
    namespace InnerLogic {
        inline void fillSprites(std::vector<SimpleSprite*> &sprites, const Types::ElementTypes type, const int num,
                                const sf::Vector2f &scale) {
            if (type >= ANIMATED_TYPES_START) {
                const auto &info = Constants::ANIMATED_SPRITE_INFO[static_cast<size_t>(type) - static_cast<size_t>(ANIMATED_TYPES_START)];
                sprites.reserve(info.src.size());
                for (auto &src : info.src) {
                    sprites.push_back(new AnimatedSprite(
                        src + std::to_string(num) + ".png",
                        info.frame_amount, info.frame_time, info.z_index));
                }
            }
            else {
                const auto &info = Constants::SIMPLE_SPRITE_INFO[static_cast<size_t>(type)];
                sprites.reserve(info.src.size());
                for (auto &src : info.src)
                    sprites.push_back(new SimpleSprite(src + std::to_string(num) + ".png", info.z_index));
            }
        
            for (auto *sprite : sprites)
                sprite->setScale(scale);
        }
    }
    
    /**
     * Create an element with specified properties.
     * @param point The position of the element.
     * @param angle The rotation angle of the element.
     * @param type The type of the element.
     * @param num The element number.
     * @param scale The scaling factor for the element (default is 1.0).
     * @return A pointer to the newly created Element.
     * @note Memory is allocated for the Element, and it is the caller's responsibility to free this memory.
     */
    inline Element *create(const sf::Vector2f &point, const float angle, const Types::ElementTypes type, const int num,
            const sf::Vector2f &scale = {1.0f, 1.0f}) {
        std::vector<SimpleSprite*> sprites;
        InnerLogic::fillSprites(sprites, type, num, scale);

        const auto size_x = static_cast<float>(sprites[0]->getTextureRect().width);
        const auto size_y = static_cast<float>(sprites[0]->getTextureRect().height);

        for (size_t i = 1; i < sprites.size(); ++i)
            delete sprites[i];
        
        return new Element(
                new Rectangle(point, size_x * scale.x, size_y * scale.y, angle),
                sprites[0],
                Constants::id_tracker.generate(type));
    }
    /**
     * Create a replaceable element with specified properties.
     * @param point The position of the element.
     * @param angle The rotation angle of the element.
     * @param type The type of the element.
     * @param num The element number.
     * @param scale The scaling factor for the element (default is 1.0).
     * @return A pointer to the newly created ReplaceableElement.
     * @note Memory is allocated for the ReplaceableElement, and it is the caller's responsibility to free this memory.
     */
    inline ReplaceableElement *createReplaceable(const sf::Vector2f &point, const float angle,
            const Types::ElementTypes type, const int num, const sf::Vector2f &scale = {1.0f, 1.0f}) {
        std::vector<SimpleSprite*> sprites;
        InnerLogic::fillSprites(sprites, type, num, scale);

        const auto size_x = static_cast<float>(sprites[0]->getTextureRect().width);
        const auto size_y = static_cast<float>(sprites[0]->getTextureRect().height);
        return new ReplaceableElement(
            new Rectangle(point, size_x * scale.x, size_y * scale.y, angle),
            sprites,
            Constants::id_tracker.generate(type));
    }
}