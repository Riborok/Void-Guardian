#include "../../../../include/game/entity/component/EntityComponent.hpp"

EntityComponent::EntityComponent(const size_t num, const size_t id): Identifiable(id), _num(num) { }

size_t EntityComponent::getNum() const { return _num; }