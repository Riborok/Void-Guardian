#pragma once

constexpr size_t ELEMENT_TYPES_COUNT = 5;
enum class ElementTypes final : size_t {
    // Simple
    BACKGROUND = 0,
    BLOCK,
    GUN,

    // Animated
    WRAITH,

    // Animation
    WRAITH_DYING
};
constexpr ElementTypes ANIMATED_TYPES_START = ElementTypes::WRAITH;
constexpr ElementTypes ANIMATION_TYPES_START = ElementTypes::WRAITH_DYING;
inline size_t toSizeT(const ElementTypes element_type) {
    return static_cast<size_t>(element_type);
}