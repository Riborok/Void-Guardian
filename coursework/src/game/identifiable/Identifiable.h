#pragma once
#include <typeindex>

class Identifiable {
    int _id;
public:
    virtual ~Identifiable() noexcept = default;
    
    int GetId() const { return _id; }
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
    explicit Identifiable(const int id) : _id(id) { }
};

struct IdentifiableHash {
    std::size_t operator()(const Identifiable *ptr) const {
        return std::hash<int>{}(ptr->GetId());
    }
};