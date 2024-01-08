#pragma once

struct CharacterLimits final {
    size_t start_index;
    size_t last_index;
    CharacterLimits(const size_t start_index, const size_t last_index):
        start_index(start_index), last_index(last_index){}
};