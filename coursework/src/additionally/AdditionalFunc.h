﻿#pragma once

#include <cstdlib>

namespace AdditionalFunc {
    /**
     * Generates a random integer between the specified minimum and maximum values, inclusive.
     * @param min The minimum value of the range.
     * @param max The maximum value of the range.
     * @returns A random integer within the specified range.
     */
    inline int GetRandom(const int min, const int max) {
        return rand() % (max - min + 1) + min;
    }
}