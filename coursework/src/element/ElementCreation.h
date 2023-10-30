﻿#pragma once
#include <string>

#include "Element.h"
#include "../additionally/Constants.h"
#include "../additionally/Types.h"
#include "../game/identifiable/IdTracker.h"
#include "../model/entity/RectangularEntity.h"
#include "../sprite/AnimatedSprite.h"
#include "../sprite/SimpleSprite.h"

namespace ElementCreation {
    namespace InnerLogic {
        IdTracker id_tracker;
    }
    inline Element *create(const sf::Vector2f &point, const float angle, const Types::ElementTypes type, const int num,
            const float scale = 1.0f) {
        std::vector<SimpleSprite*> sprites;
        
        if (type >= ANIMATED_TYPES_START) {
            const auto &info = Constants::ANIMATED_SPRITE_INFO[type - ANIMATED_TYPES_START];
            for (auto &src : info.first.first) {
                sprites.push_back(new AnimatedSprite(
                    src + std::to_string(num) + ".png",
                    info.first.second, info.second.first, info.second.second));
            }
        }
        else {
            const auto &info = Constants::SIMPLE_SPRITE_INFO[type];
            for (auto &src : info.first)
                sprites.push_back(new SimpleSprite(src + std::to_string(num) + ".png", info.second));
        }
        
        sprites[0]->setPosition(point);
        sprites[0]->setRotation(angle);
        for (auto *sprite : sprites)
            sprite->setScale(scale, scale);

        const auto size = static_cast<sf::Vector2f>(sprites[0]->getTexture()->getSize());
        return new Element(
            new RectangularEntity(point, size.x * scale, size.y * scale, angle),
            sprites,
            InnerLogic::id_tracker.generate(type));
    }
}