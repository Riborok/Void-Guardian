#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "SimpleSprite.h"

class AnimatedSprite final : public SimpleSprite {
    sf::IntRect _texture_rect;
    int _frame_width;
    int _frame_amount;
    int _frame_time;
    int _elapsed_time = 0;
public:
    AnimatedSprite(const std::string &src, const int frame_amount, const int frame_time,
            const int z_index): SimpleSprite(src, z_index), _frame_amount(frame_amount), _frame_time(frame_time) {
        
        const auto size = _texture.getSize();
        _frame_width = static_cast<int>(size.x) / _frame_amount;
        _texture_rect = sf::IntRect(0, 0, _frame_width, static_cast<int>(size.y));
        
        setTextureRect(_texture_rect);
    }

    void changeState(const int delta_time) {
        _elapsed_time += delta_time;
        if (_elapsed_time >= _frame_time) {
            _elapsed_time = 0;
            _texture_rect.left += _frame_width;
            if (_texture_rect.left >= _frame_width * _frame_amount) { _texture_rect.left = 0; }
            setTextureRect(_texture_rect);
        }
    }

    ~AnimatedSprite() noexcept override = default;
    
    AnimatedSprite(const AnimatedSprite&) noexcept = delete;
    AnimatedSprite& operator=(const AnimatedSprite&) noexcept = delete;
    AnimatedSprite(AnimatedSprite&&) noexcept = delete;
    AnimatedSprite& operator=(AnimatedSprite&&) noexcept = delete;
};