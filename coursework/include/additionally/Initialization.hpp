#pragma once
#include <algorithm>
#include "../element/ElementType.hpp"

template <typename T>
struct ElementInitializationInfo final {
    ElementType element_type;
    T info;
    ElementInitializationInfo(const ElementType element_type, T &&info):
        element_type(element_type), info(std::move(info)) { }
};

template <typename T>
using ElementInitializationList = std::initializer_list<ElementInitializationInfo<T>>;

#ifndef NDEBUG
    template <typename T>
    bool checkUniqueElementTypes(const ElementInitializationList<T> &list) {
        bool used[ELEMENT_TYPES_COUNT] = {false};

        for (const auto& curr_info : list) {
            const size_t index = toSizeT(curr_info.element_type);
            if (used[index])
                return false;
            used[index] = true;
        }

        return true; 
    }
#endif