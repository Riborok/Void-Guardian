#pragma once
#include "Executor.hpp"
#include "../entity/EntityMaps.hpp"

class RegenerationExecutor final : public Executor {
    FightingMaps *_fighting_maps;
public:
    explicit RegenerationExecutor(FightingMaps &fighting_maps);
    void handle(const int delta_time) override;

    ~RegenerationExecutor() noexcept override = default;
    RegenerationExecutor(RegenerationExecutor&&) noexcept = default;
    RegenerationExecutor& operator=(RegenerationExecutor&&) noexcept = delete;
    RegenerationExecutor(const RegenerationExecutor&) noexcept = delete;
    RegenerationExecutor& operator=(const RegenerationExecutor&) noexcept = delete;
};
