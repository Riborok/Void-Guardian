#include "../../../include/game/game handlers/Render.hpp"

void Render::add(Executor *executor) {
    _executioners.push_back(executor);
}

void Render::renderAll(const int delta_time) const {
    for (auto *executioner : _executioners)
        executioner->handle(delta_time);
}

Render::~Render() noexcept {
    for (const auto *executioner : _executioners)
        delete executioner;
}