#pragma once
#include "Executor.hpp"

class BulletExecutor final : public Executor {
public:

    void handle(const int delta_time) override;
    
    ~BulletExecutor() noexcept override;
    
    BulletExecutor(BulletExecutor&&) noexcept = default;
    BulletExecutor& operator=(BulletExecutor&&) noexcept = default;
        
    BulletExecutor(const BulletExecutor&) noexcept = delete;
    BulletExecutor& operator=(const BulletExecutor&) noexcept = delete;
};
