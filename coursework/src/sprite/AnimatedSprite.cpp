#include "../../include/sprite/AnimatedSprite.hpp"

AnimatedSprite::AnimatedSprite(const std::string &src, const int frame_count, const int frame_time, const int z_index)
    : SimpleSprite(src, z_index),
      _frame_count(frame_count),
      _frame_time(frame_time),
      _frame_width(static_cast<int>(_texture.getSize().x) / frame_count),
      _texture_rect(0, 0, _frame_width, static_cast<int>(_texture.getSize().y)) {
    setTextureRect(_texture_rect);
}

void AnimatedSprite::changeState(const int delta_time) {
    _elapsed_time += delta_time;
    if (_elapsed_time >= _frame_time) {
        _elapsed_time = 0;
        _texture_rect.left += _frame_width;
        if (_texture_rect.left >= _frame_width * _frame_count) {
            _texture_rect.left = 0;
        }
        setTextureRect(_texture_rect);
    }
}

bool AnimatedSprite::isAnimationRestarted() const {
    return _elapsed_time == 0 && _texture_rect.left == 0;
}