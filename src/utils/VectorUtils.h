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


#endif //VECTORUTILS_H
