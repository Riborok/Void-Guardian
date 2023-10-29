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
        const std::pair<std::vector<std::string>, int> SIMPLE_SPRITE_INFO[] {
            std::make_pair(std::vector<std::string>{"./img/guns/Gun_"}, 1),
        };
        
        const std::pair<std::pair<std::vector<std::string>, int>, std::pair<int, int>> ANIMATED_SPRITE_INFO[] {
            std::make_pair(std::make_pair(std::vector<std::string>{"./img/wraiths/Wraith_", "./img/wraiths/Wraith_walking_"}, 12), std::make_pair(40, 0)),
        };
        IdGenerator id_generator;
    }
    inline Element *create(const sf::Vector2f &point, const float angle, const Types::ElementType type, const int num,
            const float scale = 1.0f) {
        std::vector<SimpleSprite*> sprites;
        
        if (type >= Types::ElementType::WRAITH) {
            const auto &info = InnerLogic::ANIMATED_SPRITE_INFO[type - Types::ElementType::WRAITH];
            for (auto &src : info.first.first) {
                sprites.emplace_back(new AnimatedSprite(
                    src + std::to_string(num) + ".png",
                    info.first.second, info.second.first, info.second.second));
            }
        }
        else {
            const auto &info = InnerLogic::SIMPLE_SPRITE_INFO[type];
            for (auto &src : info.first)
                sprites.emplace_back(new SimpleSprite(src + std::to_string(num) + ".png", info.second));
        }
        
        sprites[0]->setPosition(point);
        sprites[0]->setRotation(angle);
        for (auto *sprite : sprites)
            sprite->setScale(scale, scale);

        const sf::Vector2u size = sprites[0]->getTexture()->getSize();
        return new Element(
            new RectangularEntity(point, static_cast<float>(size.x) * scale, static_cast<float>(size.y) * scale, angle),
            sprites,
            InnerLogic::id_generator.generate(type));
    }
}