#pragma once

class Identifiable {
    size_t _id;
public:
    virtual ~Identifiable() noexcept = default;

    [[nodiscard]] size_t getId() const { return _id; }
    bool operator==(const Identifiable &other) const;
    bool operator!=(const Identifiable &other) const;
    
    Identifiable(const Identifiable&) noexcept = default;
    Identifiable& operator=(const Identifiable&) noexcept = default;
    Identifiable(Identifiable&&) noexcept = default;
    Identifiable& operator=(Identifiable&&) noexcept = default;
protected:
    explicit Identifiable(const size_t id) : _id(id) { }
};

struct IdentifiableHash final {
    size_t operator()(const Identifiable *ptr) const;
};