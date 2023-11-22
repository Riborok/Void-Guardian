#pragma once

#include <type_traits>

#include "../game/identifiable/Identifiable.hpp"
#include "../geometry/collision/Axis.hpp"
#include "../model/polygon/Rectangle.hpp"

class Boundary final : public Rectangle {
    std::vector<Axis> _axes;
public:
    explicit Boundary(const AlignedRectangleData &data);
    [[nodiscard]] const std::vector<Axis> &getAxes() const;

    ~Boundary() noexcept override = default;
    Boundary& operator=(Boundary&&) noexcept = default;
    Boundary(Boundary&&) noexcept = default;
        
    Boundary(const Boundary&) noexcept = delete;
    Boundary& operator=(const Boundary&) noexcept = delete;
};

template <typename T>
class RequiresIdentifiableWithGetPolygon final {
    template <typename U, typename = std::enable_if_t<
        std::is_same_v<decltype(std::declval<U>().getPolygon()), const Polygon&> &&
        std::is_base_of_v<Identifiable, U>>>
    // ReSharper disable once CppFunctionIsNotImplemented
    static std::true_type test(int);
    
    template <typename U>
    // ReSharper disable once CppFunctionIsNotImplemented
    static std::false_type test(...);
public:
    static constexpr bool VALUE = std::is_same_v<decltype(test<T>(0)), std::true_type>;
};