#pragma once
#include <SFML/Graphics/Texture.hpp>

#include "AbstractSpriteInfo.hpp"

struct SimpleSpriteInfo {
    sf::Texture texture;
    int z_index;
    SimpleSpriteInfo(const AbstractSimpleSpriteInfo &abstract_simple_sprite_info, const size_t num) : z_index(abstract_simple_sprite_info.z_index) {
        texture.loadFromFile(abstract_simple_sprite_info.src + std::to_string(num) + ".png");
    }
};

struct AnimationSpriteInfo final : SimpleSpriteInfo {
    FrameInfo frame_info;
    AnimationSpriteInfo(const AbstractAnimationSpriteInfo &abstract_animation_sprite_info, const size_t num) :
        SimpleSpriteInfo(abstract_animation_sprite_info, num),
        frame_info(abstract_animation_sprite_info.frame_info_container.get(num)){}
};