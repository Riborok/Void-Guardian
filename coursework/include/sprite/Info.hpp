#pragma once
#include <SFML/Graphics/Texture.hpp>

#include "AbstractInfo.hpp"

struct SimpleInfo {
    sf::Texture texture;
    int z_index;
    SimpleInfo(const AbstractSimpleInfo &abstract_simple_info, const size_t num) : z_index(abstract_simple_info.z_index) {
        texture.loadFromFile(abstract_simple_info.src + std::to_string(num) + ".png");
    }
};

struct AnimationInfo final : SimpleInfo {
    FrameInfo frame_info;
    AnimationInfo(const AbstractAnimationInfo &abstract_animation_info, const size_t num) :
        SimpleInfo(abstract_animation_info, num),
        frame_info(abstract_animation_info.frame_info_container.get(num)){}
};