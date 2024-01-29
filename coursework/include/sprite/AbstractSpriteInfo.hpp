#pragma once
#include <string>

#include "FrameInfoContainer.hpp"

struct AbstractSimpleSpriteInfo {
    std::string src;
    int z_index;
    AbstractSimpleSpriteInfo(std::string &&src, const int z_index) : src(std::move(src)), z_index(z_index) {}
};

struct AbstractAnimationSpriteInfo final : AbstractSimpleSpriteInfo {
    FrameInfoContainer frame_info_container;
    AbstractAnimationSpriteInfo(FrameInfoContainer &&frame_info_container, std::string &&src_, const int z_index_) :
        AbstractSimpleSpriteInfo(std::move(src_), z_index_), frame_info_container(std::move(frame_info_container)) {}
};