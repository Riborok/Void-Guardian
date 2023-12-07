#include "../../include/element/ElementCreator.hpp"

#include "../../include/additionally/AdditionalFunc.hpp"
#include "../../include/geometry/Vector2Rotation.hpp"
#include "../../include/model/rectangle/Rectangle.hpp"
#include "../../include/sprite/AnimatedSprite.hpp"

sf::Vector2f ElementCreator::calcPoint0(const ElementData& element_data,  const sf::Vector2f& size,
        const sf::Vector2f& size_factor) {
    sf::Vector2f displacement_vector(size.x * size_factor.x, size.y * size_factor.y);
    Vector2Rotation::rotateVector2(displacement_vector, element_data.angle);
    return element_data.point + displacement_vector;
}

Element *ElementCreator::create(const ElementData &element_data) {
    SimpleSprite* sprite = createSprite(element_data);

    const auto size(AdditionalFunc::getScaledSize(sprite->getSize(), element_data.scale));
    return new Element(
        new Rectangle({element_data.point, size, element_data.angle}),
        sprite,
        element_data.scale,
        _id_tracker.generate(element_data.type));
}

Element *ElementCreator::create(const ElementData &element_data, const sf::Vector2f& size_factor) {
    SimpleSprite* sprite = createSprite(element_data);

    const auto size(AdditionalFunc::getScaledSize(sprite->getSize(), element_data.scale));
    return new Element(
        new Rectangle({calcPoint0(element_data, size, size_factor), size, element_data.angle}),
        sprite,
        element_data.scale,
        _id_tracker.generate(element_data.type));
}

ReplaceableElement *ElementCreator::createReplaceable(const ElementData &element_data) {
    ReplaceableSprites sprites; fillSprites(sprites, element_data);

    const auto size(AdditionalFunc::getScaledSize(sprites[0]->getSize(), element_data.scale));
    return new ReplaceableElement(
        new Rectangle({element_data.point, size, element_data.angle}),
        std::move(sprites),
        element_data.scale,
        _id_tracker.generate(element_data.type));
}

Element *ElementCreator::createReplaceable(const ElementData &element_data, const sf::Vector2f& size_factor) {
    ReplaceableSprites sprites; fillSprites(sprites, element_data);

    const auto size(AdditionalFunc::getScaledSize(sprites[0]->getSize(), element_data.scale));
    return new ReplaceableElement(
        new Rectangle({calcPoint0(element_data, size, size_factor), size, element_data.angle}),
        std::move(sprites),
        element_data.scale,
        _id_tracker.generate(element_data.type));
}

SimpleSprite *ElementCreator::createSprite(const ElementData &element_data) {
    SimpleSprite* result;
    if (element_data.type >= ANIMATED_TYPES_START) {
        const auto &infos = _animated_sprite_info.getInfo(element_data.type, element_data.num);
        result = new AnimatedSprite(infos[0]);
    }
    else {
        const auto &infos = _simple_sprite_info.getInfo(element_data.type, element_data.num);
        result = new SimpleSprite(infos[0]);
    }
    return result; 
}

void ElementCreator::fillSprites(ReplaceableSprites &sprites, const ElementData &element_data) {
    if (element_data.type >= ANIMATED_TYPES_START) {
        const auto &infos = _animated_sprite_info.getInfo(element_data.type, element_data.num);
        sprites.reserve(infos.size());
        for (const auto &info : infos)
            sprites.push_back(new AnimatedSprite(info));
    }
    else {
        const auto &infos = _simple_sprite_info.getInfo(element_data.type, element_data.num);
        sprites.reserve(infos.size());
        for (const auto &info : infos)
            sprites.push_back(new SimpleSprite(info));
    }
}

ElementCreator::ElementCreator(SimpleSpriteInfos &&simple_sprite_info, AnimatedSpriteInfos &&animated_sprite_info) :
    _simple_sprite_info(std::move(simple_sprite_info)), _animated_sprite_info(std::move(animated_sprite_info)) { }