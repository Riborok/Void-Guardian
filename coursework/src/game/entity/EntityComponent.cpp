﻿#include "../../../include/game/entity/EntityComponent.hpp"

EntityComponent::EntityComponent(const Element& element, const int num):
    Identifiable(element),  _num(num) { }

int EntityComponent::getNum() const { return _num; }