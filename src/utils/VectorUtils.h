//
// Created by dideldumm on 06.10.24.
//

#ifndef VECTORUTILS_H
#define VECTORUTILS_H
#include <vector>

template<typename T>
void remove_element_from_vector(std::vector<T> &vector, const T &element) {
    auto it = std::ranges::find(vector, element);
    if (it != vector.end()) {
        vector.erase(it);
    }
}

template<typename T>
void remove_all_from_vector(std::vector<T> &vector, const auto &elements) {
    for (T element: elements) {
        remove_element_from_vector(vector, element);
    }
}

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


#endif //VECTORUTILS_H
