#pragma once
#include <utility>
#include <string>

#include "Element.h"
#include "../additionally/Types.h"
#include "../game/identifiable/IDGenerator.h"
#include "../model/entity/RectangularEntity.h"
#include "../sprite/AnimatedSprite.h"
#include "../sprite/SimpleSprite.h"

namespace ElementCreation {
    namespace InnerLogic {
        const std::pair<std::string, int> SIMPLE_SPRITE_INFO[] {
            std::make_pair("./img/Guns/Gun_", 1),
        };
        
        const std::pair<std::pair<std::string, int>, std::pair<int, int>> ANIMATED_SPRITE_INFO[] {
            std::make_pair(std::make_pair("./img/Wraiths/Wraith_", 12), std::make_pair(35, 0)),
        };
        IdGenerator id_generator;
    }
    inline Element *create(const sf::Vector2f &point, const float angle, const Types::ElementType type, const int num) {
        SimpleSprite *sprite;
        
        if (type >= Types::ElementType::WRAITH) {
            const auto &info = InnerLogic::ANIMATED_SPRITE_INFO[type - Types::ElementType::WRAITH];
            
            sprite = new AnimatedSprite(info.first.first + std::to_string(num) + ".png",
                info.first.second, info.second.first, info.second.second);
        }
        else {
            const auto &info = InnerLogic::SIMPLE_SPRITE_INFO[type];
            
            sprite = new SimpleSprite(info.first + std::to_string(num) + ".png", info.second);
        }

        const sf::Vector2u size = sprite->getTexture()->getSize();
        return new Element(
            new RectangularEntity(point, static_cast<float>(size.x), static_cast<float>(size.y), angle),
            sprite,
            InnerLogic::id_generator.generate(type));
    }
}