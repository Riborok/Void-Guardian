#pragma once
#include <SFML/Graphics/Texture.hpp>

#include "AbstractInfo.hpp"

struct SimpleInfo {
    sf::Texture texture;
    int z_index;
    SimpleInfo(const AbstractSimpleInfo &abstract_simple_info, const int num) : z_index(abstract_simple_info.z_index) {
        texture.loadFromFile(abstract_simple_info.src + std::to_string(num) + ".png");
    }
};

struct AnimationInfo final : SimpleInfo {
    int frame_count;
    int frame_time;
    AnimationInfo(const AbstractAnimationInfo &abstract_animation_info, const int num) :
        SimpleInfo(abstract_animation_info, num),
        frame_count(abstract_animation_info.frame_count),
        frame_time(abstract_animation_info.frame_time) {}
};