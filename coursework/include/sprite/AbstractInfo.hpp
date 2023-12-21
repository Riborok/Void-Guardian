#pragma once
#include <string>

#include "FrameInfoContainer.hpp"

struct AbstractSimpleInfo {
    std::string src;
    int z_index;
    AbstractSimpleInfo(std::string &&src, const int z_index) : src(std::move(src)), z_index(z_index) {}
};

struct AbstractAnimationInfo final : AbstractSimpleInfo {
    FrameInfoContainer frame_info_container;
    AbstractAnimationInfo(FrameInfoContainer &&frame_info_container, std::string &&src_, const int z_index_) :
        AbstractSimpleInfo(std::move(src_), z_index_), frame_info_container(std::move(frame_info_container)) {}
};