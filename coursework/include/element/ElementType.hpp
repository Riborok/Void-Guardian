﻿#pragma once
#include <functional>

enum class ElementType final : size_t {
    // Simple
    BACKGROUND = 0,
    GUN,
    BULLET,
    BLOCK,

    // Animated
    WRAITH,

    // Animation
    WRAITH_DYING
};
constexpr size_t ELEMENT_TYPES_COUNT = static_cast<size_t>(ElementType::WRAITH_DYING) + 1;
constexpr ElementType ANIMATED_TYPES_START = ElementType::WRAITH;
constexpr ElementType ANIMATION_TYPES_START = ElementType::WRAITH_DYING;
inline size_t toSizeT(const ElementType element_type) {
    return static_cast<size_t>(element_type);
}

struct ElementTypesHash final {
    size_t operator()(const ElementType& value) const {
        return std::hash<size_t>{}(toSizeT(value));
    }
};