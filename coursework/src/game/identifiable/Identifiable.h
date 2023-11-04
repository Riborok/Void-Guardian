#pragma once
#include <typeindex>

class Identifiable {
    size_t _id;
public:
    virtual ~Identifiable() noexcept = default;
    
    size_t getId() const { return _id; }
    bool operator==(const Identifiable &other) const {
        return _id == other._id;
    }
    bool operator!=(const Identifiable &other) const {
        return _id != other._id;
    }
    
    Identifiable(const Identifiable&) noexcept = default;
    Identifiable& operator=(const Identifiable&) noexcept = default;
    Identifiable(Identifiable&&) noexcept = default;
    Identifiable& operator=(Identifiable&&) noexcept = default;
protected:
    explicit Identifiable(const size_t id) : _id(id) { }
};

struct IdentifiableHash {
    size_t operator()(const Identifiable *ptr) const {
        return std::hash<size_t>{}(ptr->getId());
    }
};