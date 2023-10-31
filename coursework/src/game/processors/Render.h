#pragma once
#include <vector>

#include "../../additionally/Types.h"

class Render final {
    std::vector<Types::Executor*> _executioners;
public:
    void add(Types::Executor *executor) { _executioners.push_back(executor); }
    void renderAll(const int delta_time) const {
        for (auto *executioner : _executioners)
            executioner->handle(delta_time);
    }

    ~Render() noexcept {
        for (const auto *executioner : _executioners)
            delete executioner;
    }
    Render() noexcept = default;
    
    Render(const Render&) noexcept = delete;
    Render& operator=(const Render&) noexcept = delete;
    Render(Render&&) noexcept = delete;
    Render& operator=(Render&&) noexcept = delete;
};