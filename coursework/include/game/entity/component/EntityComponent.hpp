#pragma once
#include "../../../element/Element.hpp"
#include "../../identifiable/Identifiable.hpp"

class EntityComponent : public Identifiable {
protected:
    int _num;
    EntityComponent(const Element &element, const int num);
public:
    [[nodiscard]] int getNum() const;
    
    ~EntityComponent() noexcept override = default;
    EntityComponent(EntityComponent&&) noexcept = default;
    EntityComponent& operator=(EntityComponent&&) noexcept = default;
    EntityComponent(const EntityComponent&) noexcept = delete;
    EntityComponent& operator=(const EntityComponent&) noexcept = delete;
};
