﻿#include "../../include/element/ElementCreator.hpp"

#include "../../include/additionally/RandomGenerator.hpp"
#include "../../include/geometry/SizeUtils.hpp"
#include "../../include/geometry/Vector2Rotation.hpp"
#include "../../include/model/rectangle/Rectangle.hpp"
#include "../../include/sprite/AnimatedSprite.hpp"

const sf::Vector2f ElementCreator::NO_OFFSET_FACTOR{0, 0};

sf::Vector2f ElementCreator::calcPoint0(const ElementInfo& element_info,  const sf::Vector2f& size,
        const sf::Vector2f& offset_factor) {
    sf::Vector2f displacement_vector(size.x * offset_factor.x, size.y * offset_factor.y);
    Vector2Rotation::rotateVector2(displacement_vector, element_info.angle);
    return element_info.point + displacement_vector;
}

Element *ElementCreator::create(const ElementInfo &element_info, const sf::Vector2f& offset_factor) {
    SimpleSprite* sprite = createSprite(element_info);

    const auto size(SizeUtils::getScaledSize(sf::Vector2f{sprite->getWidth(), sprite->getHeight()}, element_info.scale));
    return new Element(
        new Rectangle({
            &offset_factor == &NO_OFFSET_FACTOR ? element_info.point : calcPoint0(element_info, size, offset_factor),
            size, element_info.angle}),
        sprite,
        element_info.scale,
        _id_tracker.generate(element_info.type)
    );
}

ReplaceableElement *ElementCreator::createReplaceable(const ElementInfo &element_info, const sf::Vector2f& offset_factor) {
    ReplaceableSprites sprites; fillSprites(sprites, element_info);

    const auto size(SizeUtils::getScaledSize(sf::Vector2f{sprites[0]->getWidth(), sprites[0]->getHeight()}, element_info.scale));
    return new ReplaceableElement(
        new Rectangle({
            &offset_factor == &NO_OFFSET_FACTOR ? element_info.point : calcPoint0(element_info, size, offset_factor),
            size, element_info.angle}),
        std::move(sprites),
        element_info.scale,
        _id_tracker.generate(element_info.type));
}

void ElementCreator::loadTexture(const ElementType element_type, const size_t num) {
    if (element_type >= ANIMATED_TYPES_START)
        _animated_sprite_info.addInfoFromAbstract(element_type, num);
    else
        _simple_sprite_info.addInfoFromAbstract(element_type, num);
}

void ElementCreator::setDefaultZIndex(const Element &element, const size_t num) {
    if (const ElementType type = ElementIdTracker::extractType(element.getId()); type >= ANIMATED_TYPES_START) {
        const auto &infos = _animated_sprite_info.getInfo(type, num);
        element.setZIndex(infos[0].z_index);
    }
    else {
        const auto &infos = _simple_sprite_info.getInfo(type, num);
        element.setZIndex(infos[0].z_index);
    }
}

SimpleSprite *ElementCreator::createSprite(const ElementInfo &element_info) {
    SimpleSprite* result;
    if (element_info.type >= ANIMATED_TYPES_START) {
        const auto &infos = _animated_sprite_info.getInfo(element_info.type, element_info.num);
        result = new AnimatedSprite(infos[0]);
    }
    else {
        const auto &infos = _simple_sprite_info.getInfo(element_info.type, element_info.num);
        result = new SimpleSprite(infos[0]);
    }
    return result; 
}

void ElementCreator::fillSprites(ReplaceableSprites &sprites, const ElementInfo &element_info) {
    if (element_info.type >= ANIMATED_TYPES_START) {
        const auto &infos = _animated_sprite_info.getInfo(element_info.type, element_info.num);
        sprites.reserve(infos.size());
        for (const auto &info : infos)
            sprites.push_back(new AnimatedSprite(info));
    }
    else {
        const auto &infos = _simple_sprite_info.getInfo(element_info.type, element_info.num);
        sprites.reserve(infos.size());
        for (const auto &info : infos)
            sprites.push_back(new SimpleSprite(info));
    }
}

ElementCreator::ElementCreator(const SimpleSpriteInfos& simple_sprite_info,
                               const AnimatedSpriteInfos& animated_sprite_info):
        _simple_sprite_info(simple_sprite_info), _animated_sprite_info(animated_sprite_info) { }