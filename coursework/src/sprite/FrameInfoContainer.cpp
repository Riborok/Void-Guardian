#include "../../include/sprite/FrameInfoContainer.hpp"

#include <stdexcept>

size_t FrameInfoContainer::binarySearch(const size_t index) const noexcept(false) {
    size_t low = 0;
    size_t high = _frame_infos.size() - 1;
    while (low <= high) {
        if (const size_t mid = (high + low) / 2; index <= _frame_infos[mid].last_index) {
            if (mid == 0 || index > _frame_infos[mid - 1].last_index)
                return mid;
            high = mid - 1;
        }
        else
            low = mid + 1;
    }
    throw std::out_of_range("Index not found in FrameInfoContainer");
}

FrameInfoContainer::FrameInfoContainer(FrameInfos&& frame_infos):
        _frame_infos(std::move(frame_infos)){}

const FrameInfo& FrameInfoContainer::get(const size_t index) const noexcept(false) {
    if (_frame_infos.size() == 1) { return _frame_infos[0].frame_info; }
    return _frame_infos[binarySearch(index)].frame_info;
}