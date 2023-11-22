#include "../../include/element/ElementCreator.hpp"

#include "../../include/model/polygon/Rectangle.hpp"
#include "../../include/sprite/AnimatedSprite.hpp"

sf::Vector2f getSize(const SimpleSprite &sprite) {
    return { static_cast<float>(sprite.getTextureRect().width),
        static_cast<float>(sprite.getTextureRect().height) };
}

void setPosAndAngle(SimpleSprite &sprite, const sf::Vector2f &point, const float angle) {
    sprite.setPosition(point);
    sprite.setRotation(angle);
}

Element *ElementCreator::create(const ElementData &element_data) {
    SimpleSprite* sprite = createSprite(element_data);
    
    setPosAndAngle(*sprite, element_data.point, element_data.angle);
    return new Element(
        new Rectangle({element_data.point, AdditionalFunc::getScaledSize(getSize(*sprite), element_data.scale),
            element_data.angle}),
        sprite,
        _id_tracker.generate(element_data.type));
}

ReplaceableElement *ElementCreator::createReplaceable(const ElementData &element_data) {
    std::vector<SimpleSprite*> sprites; fillSprites(sprites, element_data);
    
    setPosAndAngle(*sprites[0], element_data.point, element_data.angle);
    return new ReplaceableElement(
        new Rectangle({element_data.point, AdditionalFunc::getScaledSize(getSize(*sprites[0]), element_data.scale),
            element_data.angle}),
        std::move(sprites),
        _id_tracker.generate(element_data.type));
}

SimpleSprite* ElementCreator::createSprite(const ElementData &element_data) const {
    SimpleSprite* result;
    if (element_data.type >= ANIMATED_TYPES_START) {
        const auto &info = _animated_sprite_info[toSizeT(element_data.type) - toSizeT(ANIMATED_TYPES_START)];
        result = new AnimatedSprite(
                info.src[0] + std::to_string(element_data.num) + ".png",
                info.frame_count, info.frame_time, info.z_index);
    }
    else {
        const auto &info = _simple_sprite_info[toSizeT(element_data.type)];
        result = new SimpleSprite(info.src[0] + std::to_string(element_data.num) + ".png", info.z_index);
    }
    result->setScale(element_data.scale);
    return result; 
}

void ElementCreator::fillSprites(std::vector<SimpleSprite*> &sprites, const ElementData &element_data) const {
    if (element_data.type >= ANIMATED_TYPES_START) {
        const auto &info = _animated_sprite_info[toSizeT(element_data.type) - toSizeT(ANIMATED_TYPES_START)];
        sprites.reserve(info.src.size());
        for (auto &src : info.src) {
            sprites.push_back(new AnimatedSprite(
                src + std::to_string(element_data.num) + ".png",
                info.frame_count, info.frame_time, info.z_index));
        }
    }
    else {
        const auto &info = _simple_sprite_info[toSizeT(element_data.type)];
        sprites.reserve(info.src.size());
        for (auto &src : info.src)
            sprites.push_back(new SimpleSprite(src + std::to_string(element_data.num) + ".png", info.z_index));
    }
    sprites[0]->setScale(element_data.scale);
}

ElementCreator::ElementCreator(const SimpleSpriteInfos &simple_sprite_info, const AnimatedSpriteInfos &animated_sprite_info) :
    _simple_sprite_info(simple_sprite_info), _animated_sprite_info(animated_sprite_info) { }