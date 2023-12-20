#pragma once

class Executor {
public:
    Executor() noexcept = default;
    virtual void handle(const int delta_time) = 0;
    
    virtual ~Executor() noexcept = default;
    Executor(Executor&&) noexcept = default;
    Executor& operator=(Executor&&) noexcept = delete;
    Executor(const Executor&) noexcept = delete;
    Executor& operator=(const Executor&) noexcept = delete;
};
