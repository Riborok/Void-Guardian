#pragma once

#include "../../additionally/Types.hpp"
#include "../processors/GameUpdater.hpp"

class SpriteStateExecutor final : public Executor {
    GameUpdater *_game_updater;
public:
    explicit SpriteStateExecutor(GameUpdater &game_updater);

    void handle(const int delta_time) override;
    
    ~SpriteStateExecutor() noexcept override = default;
    
    SpriteStateExecutor(SpriteStateExecutor&&) noexcept = default;
    SpriteStateExecutor& operator=(SpriteStateExecutor&&) noexcept = default;
        
    SpriteStateExecutor(const SpriteStateExecutor&) noexcept = delete;
    SpriteStateExecutor& operator=(const SpriteStateExecutor&) noexcept = delete;
};
