#pragma once
#include <SFML/System/Vector2.hpp>

namespace Types {
    struct CollisionResult {
         sf::Vector2f collision_point;
        float overlap;
    };

#define ANIMATED_TYPES_START Types::ElementTypes::WRAITH
    enum : int { AMOUNT_OF_ELEMENT_TYPES = 4 };
    enum ElementTypes : unsigned int {
        // Simple
        BACKGROUND = 0u,
        BLOCK,
        GUN,

        // Animated
        WRAITH,
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
}
