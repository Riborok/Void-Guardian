#include "../../include/element/ElementCreation.hpp"

#include "../../include/additionally/Constants.hpp"
#include "../../include/additionally/TypesDef.hpp"
#include "../../include/model/polygon/Rectangle.hpp"
#include "../../include/sprite/AnimatedSprite.hpp"

namespace InnerLogic {
    const SimpleSpriteInfo SIMPLE_SPRITE_INFO[]{
        {StringVector{"./img/backgrounds/Background_"}, 0},
        {StringVector{"./img/blocks/Block_"}, 1},
        {StringVector{"./img/guns/Gun_"}, 3},
    };

    const AnimatedSpriteInfo ANIMATED_SPRITE_INFO[]{
        {
            StringVector{"./img/wraiths/Wraith_", "./img/wraiths/Wraith_walking_"},
            12, 40, 2
        },
        {
            StringVector{"./img/wraiths/Wraith_dying_"},
            15, 40, 4
        }
    }; 
    
    void fillSprites(std::vector<SimpleSprite*> &sprites, const ElementTypes type, const int num,
                            const sf::Vector2f &scale) {
        if (type >= ANIMATED_TYPES_START) {
            const auto &info = ANIMATED_SPRITE_INFO[static_cast<size_t>(type) - static_cast<size_t>(ANIMATED_TYPES_START)];
            sprites.reserve(info.src.size());
            for (auto &src : info.src) {
                sprites.push_back(new AnimatedSprite(
                    src + std::to_string(num) + ".png",
                    info.frame_count, info.frame_time, info.z_index));
            }
        }
        else {
            const auto &info = SIMPLE_SPRITE_INFO[static_cast<size_t>(type)];
            sprites.reserve(info.src.size());
            for (auto &src : info.src)
                sprites.push_back(new SimpleSprite(src + std::to_string(num) + ".png", info.z_index));
        }
    
        for (auto *sprite : sprites)
            sprite->setScale(scale);
    }
    sf::Vector2f getSize(const SimpleSprite &sprite) {
        return { static_cast<float>(sprite.getTextureRect().width),
            static_cast<float>(sprite.getTextureRect().height) };
    }
    void setPosAndAngle(const sf::Vector2f &point, const float angle, SimpleSprite &sprite) {
        sprite.setPosition(point);
        sprite.setRotation(angle);
    }
}

Element *ElementCreation::create(const sf::Vector2f &point, const float angle, const ElementTypes type, const int num,
    const sf::Vector2f &scale) {
    std::vector<SimpleSprite*> sprites;
    InnerLogic::fillSprites(sprites, type, num, scale);
    
    for (size_t i = 1; i < sprites.size(); ++i)
        delete sprites[i];

    const auto size = InnerLogic::getSize(*sprites[0]);
    InnerLogic::setPosAndAngle(point, angle, *sprites[0]);
    return new Element(
            new Rectangle(point, size.x * scale.x, size.y * scale.y, angle),
            sprites[0],
            Constants::id_tracker.generate(type));
}

ReplaceableElement *ElementCreation::createReplaceable(const sf::Vector2f &point, const float angle,
    const ElementTypes type, const int num, const sf::Vector2f &scale) {
    std::vector<SimpleSprite*> sprites;
    InnerLogic::fillSprites(sprites, type, num, scale);

    const auto size = InnerLogic::getSize(*sprites[0]);
    InnerLogic::setPosAndAngle(point, angle, *sprites[0]);
    return new ReplaceableElement(
        new Rectangle(point, size.x * scale.x, size.y * scale.y, angle),
        std::move(sprites),
        Constants::id_tracker.generate(type));
}