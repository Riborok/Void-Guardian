#include "../../include/element/ElementCreator.hpp"

#include "../../include/additionally/AdditionalFunc.hpp"
#include "../../include/model/polygon/Rectangle.hpp"
#include "../../include/sprite/AnimatedSprite.hpp"

Element *ElementCreator::create(const ElementData &element_data, const sf::Vector2f &origin) {
    SimpleSprite* sprite = createSprite(element_data);
    
    return new Element(
        new Rectangle({element_data.point, AdditionalFunc::getScaledSize(sprite->getSize(), element_data.scale),
            element_data.angle}),
        sprite,
        {origin, element_data.scale},
        _id_tracker.generate(element_data.type));
}

ReplaceableElement *ElementCreator::createReplaceable(const ElementData &element_data, const sf::Vector2f &origin) {
    ReplaceableSprites sprites; fillSprites(sprites, element_data);
    
    return new ReplaceableElement(
        new Rectangle({element_data.point, AdditionalFunc::getScaledSize(sprites[0]->getSize(), element_data.scale),
            element_data.angle}),
        std::move(sprites),
        {origin, element_data.scale},
        _id_tracker.generate(element_data.type));
}

SimpleSprite *ElementCreator::createSprite(const ElementData &element_data) const {
    SimpleSprite* result;
    if (element_data.type >= ANIMATED_TYPES_START) {
        const auto &infos = _animated_sprite_info[element_data.type];
        result = new AnimatedSprite(AnimationInfo{infos[0], element_data.num});
    }
    else {
        const auto &infos = _simple_sprite_info[element_data.type];
        result = new SimpleSprite(SimpleInfo{infos[0], element_data.num});
    }
    return result; 
}

void ElementCreator::fillSprites(ReplaceableSprites &sprites, const ElementData &element_data) const {
    if (element_data.type >= ANIMATED_TYPES_START) {
        const auto &infos = _animated_sprite_info[element_data.type];
        sprites.reserve(infos.size());
        for (auto &info : infos)
            sprites.push_back(new AnimatedSprite(AnimationInfo{info, element_data.num}));
    }
    else {
        const auto &infos = _simple_sprite_info[element_data.type];
        sprites.reserve(infos.size());
        for (auto &info : infos)
            sprites.push_back(new SimpleSprite(SimpleInfo{info, element_data.num}));
    }
}

ElementCreator::ElementCreator(SimpleSpriteInfos &&simple_sprite_info, AnimatedSpriteInfos &&animated_sprite_info) :
    _simple_sprite_info(std::move(simple_sprite_info)), _animated_sprite_info(std::move(animated_sprite_info)) { }