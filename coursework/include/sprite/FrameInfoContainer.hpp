#pragma once
#include <vector>

#include "FrameInfo.hpp"

struct FrameInfoContainerEntry final {
    FrameInfo frame_info;
    size_t last_index;
    FrameInfoContainerEntry(const FrameInfo &frame_info, const size_t last_index): frame_info(frame_info), last_index(last_index) {}
};

class FrameInfoContainer final {
    std::vector<FrameInfoContainerEntry> _frame_infos;
    [[nodiscard]] size_t binarySearch(const size_t index) const noexcept(false);
public:
    explicit FrameInfoContainer(std::vector<FrameInfoContainerEntry> &&frame_infos);
    [[nodiscard]] const FrameInfo& get(const size_t index) const noexcept(false);

    ~FrameInfoContainer() noexcept = default;
    FrameInfoContainer(FrameInfoContainer&&) noexcept = default;
    FrameInfoContainer& operator=(FrameInfoContainer&&) noexcept = delete;
    FrameInfoContainer(const FrameInfoContainer&) noexcept = default;
    FrameInfoContainer& operator=(const FrameInfoContainer&) noexcept = default;
};