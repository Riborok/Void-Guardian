#pragma once
#include <vector>

#include "../../additionally/Types.hpp"

class Render final {
    std::vector<Types::Executor*> _executioners;

public:
    void add(Types::Executor *executor);
    void renderAll(const int delta_time) const;

    ~Render() noexcept;

    Render() noexcept = default;
    Render(const Render&) noexcept = delete;
    Render& operator=(const Render&) noexcept = delete;
    Render(Render&&) noexcept = delete;
    Render& operator=(Render&&) noexcept = delete;
};