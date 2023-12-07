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
    #include <unordered_set>

    typedef std::unordered_set<ElementType, ElementTypesHash> UniqueElements;

    template <typename T>
    bool checkUniqueElementTypes(const InitializerList<T> &data) {
        UniqueElements unique_elements;

        for (const auto& curr_data : data) {
            if (unique_elements.find(curr_data.element_type) != unique_elements.end())
                return false;
            unique_elements.insert(curr_data.element_type);
        }

        return true; 
    }
#endif