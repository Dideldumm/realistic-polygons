//
// Created by dideldumm on 06.10.24.
//

#ifndef VECTORUTILS_H
#define VECTORUTILS_H
#include <optional>
#include <vector>

/**
 * Searches for the given element in the given vector and removes it, if found.
 * @tparam T the type of the elements inside the vector
 * @param vector the vector to remove the element from
 * @param element the element to remove
 */
template<typename T>
void remove_element_from_vector(std::vector<T> &vector, const T &element) {
    auto it = std::ranges::find(vector, element);
    if (it != vector.end()) {
        vector.erase(it);
    }
}

/**
 * Searches for all given elements in the given vector.
 * Removes every element that is found in the vector.
 * @tparam T the type of the elements
 * @param vector the vector to remove elements from
 * @param elements the elements to remove
 */
template<typename T>
void remove_all_from_vector(std::vector<T> &vector, const auto &elements) {
    for (T element: elements) {
        remove_element_from_vector(vector, element);
    }
}

/**
 * Creates a pair for each element in the given vector with every other element inside that same vector.
 * @tparam T the type of the elements
 * @param elements the vector to build pairs from
 * @return a vector with all pairs
 */
template<typename T>
std::vector<std::pair<T, T> > createAllPairs(const std::vector<T> &elements) {
    std::vector<std::pair<T, T> > pairs = {};
    for (unsigned int i = 0; i < elements.size(); ++i) {
        for (unsigned int j = i; j < elements.size(); ++j) {
            if (i != j) {
                pairs.emplace_back(elements[i], elements[j]);
            }
        }
    }
    return pairs;
}

/**
 * Removes the first element of the given vector an returns it.
 * If the vector is empty, returns no value.
 * @tparam T the type of the elements in the vector
 * @param vector the vector to pop the first element from
 * @return the first element in the given vector or empty if the given vector has no elements
 */
template<typename T>
std::optional<T> pop_front(std::vector<T> &vector) {
    if (vector.empty()) {
        return {};
    }
    T front = vector.front();
    vector.erase(vector.begin());
    return front;
}

#endif //VECTORUTILS_H
