#pragma once
#include "../element/ElementCreator.hpp"
#include "../game/construction/LocationCreator.hpp"

struct SimpleCreators final {
    ElementCreator element_creator;
    LocationCreator location_creator;
    SimpleCreators(SimpleSpriteInfos &&simple_sprite_info, AnimatedSpriteInfos &&animated_sprite_info):
        element_creator(std::move(simple_sprite_info), std::move(animated_sprite_info)), location_creator() {}
};