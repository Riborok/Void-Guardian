#pragma once

struct FrameInfo final {
    int frame_count;
    int frame_time;
    FrameInfo(const int frame_count, const int frame_time) : frame_count(frame_count), frame_time(frame_time) {}
};