#include <typeindex>

#include "../../../include/game/identifiable/Identifiable.hpp"

bool Identifiable::operator==(const Identifiable &other) const {
    return _id == other._id;
}
bool Identifiable::operator!=(const Identifiable &other) const {
    return _id != other._id;
}

size_t IdentifiableHash::operator()(const Identifiable *ptr) const {
    return std::hash<size_t>{}(ptr->getId());
}