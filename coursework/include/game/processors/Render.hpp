#pragma once
#include <vector>

#include "../executors/Executor.hpp"

class Render final {
    typedef std::vector<Executor*> Executioners;
    
    Executioners _executioners;
public:
    void add(Executor *executor);
    void renderAll(const int delta_time) const;

    ~Render() noexcept;

    Render() noexcept = default;
    Render(const Render&) noexcept = delete;
    Render& operator=(const Render&) noexcept = delete;
    Render(Render&&) noexcept = delete;
    Render& operator=(Render&&) noexcept = delete;
};