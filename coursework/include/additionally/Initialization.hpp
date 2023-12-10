#pragma once
#include <algorithm>
#include "../element/ElementType.hpp"

template <typename T>
struct InitializerData final {
    ElementType element_type;
    T data;
    InitializerData(const ElementType element_type, T &&data):
        element_type(element_type), data(std::move(data)) { }
};

template <typename T>
using InitializerList = std::initializer_list<InitializerData<T>>;

#ifndef NDEBUG
    template <typename T>
    bool checkUniqueElementTypes(const InitializerList<T> &data) {
        bool used[ELEMENT_TYPES_COUNT] = {false};

        for (const auto& curr_data : data) {
            const size_t index = toSizeT(curr_data.element_type);
            if (used[index])
                return false;
            used[index] = true;
        }

        return true; 
    }
#endif