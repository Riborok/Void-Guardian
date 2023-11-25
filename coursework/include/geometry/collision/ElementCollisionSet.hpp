#pragma once
#include <unordered_set>
#include "../../element/Element.hpp"

typedef std::unordered_set<const Element*, IdentifiableHash> ElementCollisionSet;