#pragma once
#include <string>

struct AbstractSimpleInfo {
    std::string src;
    int z_index;
    AbstractSimpleInfo(std::string &&src, const int z_index) : src(std::move(src)), z_index(z_index) {}
};

struct AbstractAnimationInfo final : AbstractSimpleInfo {
    int frame_count;
    int frame_time;
    AbstractAnimationInfo(const int count, const int time, std::string &&src_, const int z_index_) :
        AbstractSimpleInfo(std::move(src_), z_index_), frame_count(count), frame_time(time) {}
};