﻿#pragma once

class Executor {
public:
    virtual void handle(const int delta_time) = 0;
    virtual ~Executor() noexcept = default;
    Executor() noexcept = default;
    Executor(Executor&&) noexcept = default;
    Executor& operator=(Executor&&) noexcept = default;
    
    Executor(const Executor&) noexcept = delete;
    Executor& operator=(const Executor&) noexcept = delete;
};