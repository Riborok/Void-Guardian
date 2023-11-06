#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>

namespace Types {
    struct CollisionResult {
         sf::Vector2f collision_point;
        float overlap;
    };

#define ANIMATED_TYPES_START Types::ElementTypes::WRAITH
#define ANIMATION_TYPES_START Types::ElementTypes::WRAITH_DYING
    constexpr size_t AMOUNT_OF_ELEMENT_TYPES = 5;
    enum class ElementTypes : size_t {
        // Simple
        BACKGROUND = 0,
        BLOCK,
        GUN,

        // Animated
        WRAITH,

        // Animation
        WRAITH_DYING
    };
    constexpr size_t AMOUNT_OF_OTHERS_TYPES = 1;
    constexpr size_t RECT_LOC = AMOUNT_OF_ELEMENT_TYPES;
    
    class Executor {
    public:
        virtual void handle(int delta_time) = 0;
        virtual ~Executor() noexcept = default;
        Executor() noexcept = default;
        Executor(Executor&&) noexcept = default;
        Executor& operator=(Executor&&) noexcept = default;
        
        Executor(const Executor&) noexcept = delete;
        Executor& operator=(const Executor&) noexcept = delete;
    };

    struct Control {
        sf::Keyboard::Key move;
        sf::Keyboard::Key shoot;
    };

    struct SimpleSpriteInfo {
        std::vector<std::string> src;
        int z_index;
        SimpleSpriteInfo(const std::vector<std::string> &src_, const int z_index_): src(src_), z_index(z_index_) {}
    };

    struct AnimatedSpriteInfo : SimpleSpriteInfo {
        int frame_amount;
        int frame_time;
        AnimatedSpriteInfo(const std::vector<std::string> &src_, const int frame_amount_, const int frame_time_,
            const int z_index_): SimpleSpriteInfo(src_, z_index_), frame_amount(frame_amount_), frame_time(frame_time_){}
    };
}
