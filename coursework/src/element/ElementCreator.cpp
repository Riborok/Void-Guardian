#include "../../include/element/ElementCreator.hpp"

#include "../../include/additionally/RandomGenerator.hpp"
#include "../../include/geometry/SizeUtils.hpp"
#include "../../include/geometry/Vector2Rotation.hpp"
#include "../../include/model/rectangle/Rectangle.hpp"
#include "../../include/sprite/AnimatedSprite.hpp"

const sf::Vector2f ElementCreator::NO_OFFSET_FACTOR{0, 0};

sf::Vector2f ElementCreator::calcPoint0(const ElementData& element_data,  const sf::Vector2f& size,
        const sf::Vector2f& offset_factor) {
    sf::Vector2f displacement_vector(size.x * offset_factor.x, size.y * offset_factor.y);
    Vector2Rotation::rotateVector2(displacement_vector, element_data.angle);
    return element_data.point + displacement_vector;
}

Element *ElementCreator::create(const ElementData &element_data, const sf::Vector2f& offset_factor) {
    SimpleSprite* sprite = createSprite(element_data);

    const auto size(SizeUtils::getScaledSize(sprite->getSize(), element_data.scale));
    return new Element(
        new Rectangle({
            &offset_factor == &NO_OFFSET_FACTOR ? element_data.point : calcPoint0(element_data, size, offset_factor),
            size, element_data.angle}),
        sprite,
        element_data.scale,
        _id_tracker.generate(element_data.type)
    );
}

ReplaceableElement *ElementCreator::createReplaceable(const ElementData &element_data, const sf::Vector2f& offset_factor) {
    ReplaceableSprites sprites; fillSprites(sprites, element_data);

    const auto size(SizeUtils::getScaledSize(sprites[0]->getSize(), element_data.scale));
    return new ReplaceableElement(
        new Rectangle({
            &offset_factor == &NO_OFFSET_FACTOR ? element_data.point : calcPoint0(element_data, size, offset_factor),
            size, element_data.angle}),
        std::move(sprites),
        element_data.scale,
        _id_tracker.generate(element_data.type));
}

void ElementCreator::setDefaultZIndex(const Element &element, const int num) {
    if (const ElementType type = ElementIdTracker::extractType(element.getId()); type >= ANIMATED_TYPES_START) {
        const auto &infos = _animated_sprite_info.getInfo(type, num);
        element.setZIndex(infos[0].z_index);
    }
    else {
        const auto &infos = _simple_sprite_info.getInfo(type, num);
        element.setZIndex(infos[0].z_index);
    }
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

ElementCreator::ElementCreator(const SimpleSpriteInfos& simple_sprite_info,
                               const AnimatedSpriteInfos& animated_sprite_info):
        _simple_sprite_info(simple_sprite_info), _animated_sprite_info(animated_sprite_info) { }