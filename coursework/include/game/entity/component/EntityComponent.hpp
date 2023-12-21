#pragma once
#include "../../identifiable/Identifiable.hpp"

class EntityComponent : public Identifiable {
protected:
    size_t _num;
    EntityComponent(const size_t num, const size_t id);
public:
    [[nodiscard]] size_t getNum() const;
    
    ~EntityComponent() noexcept override = default;
    EntityComponent(EntityComponent&&) noexcept = default;
    EntityComponent& operator=(EntityComponent&&) noexcept = default;
    EntityComponent(const EntityComponent&) noexcept = delete;
    EntityComponent& operator=(const EntityComponent&) noexcept = delete;
};
