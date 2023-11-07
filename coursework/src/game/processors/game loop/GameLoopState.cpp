#include "../../../../include/game/processors/game loop/GameLoopState.hpp"

void GameLoopState::changeActivity() {
    clock.restart();
    is_active = !is_active;
}