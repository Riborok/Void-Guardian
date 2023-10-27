#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

enum AnimatedSpriteType {
    WRAITH = 0,  
};

class AnimatedSprite final : public sf::Sprite {
    static const std::string SRC[][1];
    
    sf::Texture _texture;
    sf::IntRect _texture_rect;
    int _frame_width;
    int _frame_amount;
    int _frame_time;
    int _elapsed_time = 0;
public:
    AnimatedSprite(const AnimatedSpriteType type, const int num, const int frame_amount, const int frame_time) :
    _frame_amount(frame_amount), _frame_time(frame_time) {
        _texture.loadFromFile(SRC[type][num]);
        
        const auto size = _texture.getSize();
        _frame_width = static_cast<int>(size.x) / _frame_amount;
        _texture_rect = sf::IntRect(0, 0, _frame_width, static_cast<int>(size.y));

        setTexture(_texture);
        setTextureRect(_texture_rect);
    }

    void ChangeState(const int delta_time) {
        _elapsed_time += delta_time;
        if (_elapsed_time >= _frame_time) {
            _elapsed_time = 0;
            _texture_rect.left += _frame_width;
            if (_texture_rect.left >= _frame_width * _frame_amount) { _texture_rect.left = 0; }
            setTextureRect(_texture_rect);
        }
    }

    ~AnimatedSprite() noexcept override = default;
    AnimatedSprite(const AnimatedSprite&) noexcept = default;
    AnimatedSprite& operator=(const AnimatedSprite&) noexcept = default;
    AnimatedSprite(AnimatedSprite&&) noexcept = default;
    AnimatedSprite& operator=(AnimatedSprite&&) noexcept = default;
};

const std::string AnimatedSprite::SRC[][1] = {
    {
        "./img/Wraiths/Wraith_0.png",
    }
};