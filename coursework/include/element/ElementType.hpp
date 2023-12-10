#pragma once

enum class ElementType final : size_t {
    BACKGROUND = 0,
    BULLET,
    BLOCK,
    
    GUN,
    PORTAL,
    
    WRAITH,
    
    BULLET_IMPACT,
    WRAITH_DYING,
};
constexpr size_t ELEMENT_TYPES_COUNT = static_cast<size_t>(ElementType::WRAITH_DYING) + 1;

constexpr ElementType SIMPLE_TYPES_START = ElementType::BACKGROUND;
constexpr ElementType SIMPLE_TYPES_END = ElementType::GUN;

// Additional subtype
constexpr ElementType COLLECTIBLE_TYPES_START = ElementType::GUN;
constexpr ElementType COLLECTIBLE_TYPES_END = ElementType::PORTAL;

constexpr ElementType ANIMATED_TYPES_START = ElementType::PORTAL;
constexpr ElementType ANIMATED_TYPES_END = ElementType::WRAITH;

constexpr ElementType ANIMATION_TYPES_START = ElementType::BULLET_IMPACT;
constexpr ElementType ANIMATION_TYPES_END = ElementType::WRAITH_DYING;

inline size_t toSizeT(const ElementType element_type) {
    return static_cast<size_t>(element_type);
}

struct ElementTypesHash final {
    size_t operator()(const ElementType& value) const {
        return std::hash<size_t>{}(toSizeT(value));
    }
};