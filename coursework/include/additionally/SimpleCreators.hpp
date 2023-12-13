#pragma once
#include "../element/ElementCreator.hpp"
#include "../game/construction/LocationCreator.hpp"

struct SimpleCreators final {
    ElementCreator element_creator;
    LocationCreator location_creator;
    SimpleCreators(const SimpleSpriteInfos &simple_sprite_info, const AnimatedSpriteInfos &animated_sprite_info):
        element_creator(simple_sprite_info, animated_sprite_info), location_creator() {}
};