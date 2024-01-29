#include "../../include/sprite/AnimatedSprite.hpp"

AnimatedSprite::AnimatedSprite(const AnimationSpriteInfo &animation_sprite_info)
    : SimpleSprite(animation_sprite_info, animation_sprite_info.frame_info.frame_count),
      _frame_info(animation_sprite_info.frame_info),
      _frame_width(static_cast<int>(_texture->getSize().x) / animation_sprite_info.frame_info.frame_count) { }

void AnimatedSprite::changeState(const int delta_time) {
    _is_animation_restarted = false;
    _elapsed_time += delta_time;
    if (_elapsed_time >= _frame_info.frame_time) {
        _elapsed_time -= _frame_info.frame_time;
        _texture_rect.left += _frame_width;
        if (_texture_rect.left >= _frame_width * _frame_info.frame_count) {
            _texture_rect.left = 0;
            _is_animation_restarted = true;
        }
    }
}

bool AnimatedSprite::isAnimationRestarted() const { return _is_animation_restarted; }