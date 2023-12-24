#pragma once
#include <random>

struct RandomSize final {
    std::uniform_int_distribution<int> random_size_x;
    std::uniform_int_distribution<int> random_size_y;
    RandomSize(const std::uniform_int_distribution<int> &random_size_x,
        const std::uniform_int_distribution<int> &random_size_y):
    random_size_x(random_size_x), random_size_y(random_size_y) {}
};