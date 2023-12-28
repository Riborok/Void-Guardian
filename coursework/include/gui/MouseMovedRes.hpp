#pragma once

enum class MouseMovedRes final : size_t {
    DEF_CURSOR          = 0, 
    SELECTION_CURSOR    = 1 << 0,
    REDRAW              = 1 << 1,
};

constexpr bool has(const MouseMovedRes value, const MouseMovedRes flag) {
    return static_cast<size_t>(value) & static_cast<size_t>(flag);
}

constexpr MouseMovedRes operator|(const MouseMovedRes operand1, const MouseMovedRes operand2) {
    return static_cast<MouseMovedRes>(static_cast<size_t>(operand1) | static_cast<size_t>(operand2));
}

constexpr MouseMovedRes& operator|=(MouseMovedRes& operand1, const MouseMovedRes operand2) {
    operand1 = operand1 | operand2;
    return operand1;
}