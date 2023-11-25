#include "../../../../include/game/processors/game loop/GameLoopState.hpp"

GameLoopState::GameLoopState(const sf::Clock clock): clock(clock) {}

void GameLoopState::changeActivity() {
    clock.restart();
    is_active = !is_active;
}