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
    
    class Executor {
    public:
        virtual void handle(const int delta_time) = 0;
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
}
