#include "../../include/sprite/AnimatedSprite.hpp"

AnimatedSprite::AnimatedSprite(const AnimationInfo &animation_info)
    : SimpleSprite(animation_info, animation_info.frame_count),
      _frame_count(animation_info.frame_count),
      _frame_time(animation_info.frame_time),
      _frame_width(static_cast<int>(_texture->getSize().x) / animation_info.frame_count) { }

void AnimatedSprite::changeState(const int delta_time) {
    _is_animation_restarted = false;
    _elapsed_time += delta_time;
    if (_elapsed_time >= _frame_time) {
        _elapsed_time -= _frame_time;
        _texture_rect.left += _frame_width;
        if (_texture_rect.left >= _frame_width * _frame_count) {
            _texture_rect.left = 0;
            _is_animation_restarted = true;
        }
    }
}

bool AnimatedSprite::isAnimationRestarted() const { return _is_animation_restarted; }