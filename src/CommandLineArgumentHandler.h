//
// Created by dideldumm on 13.07.24.
//

#ifndef COMMANDLINEARGUMENTHANDLER_H
#define COMMANDLINEARGUMENTHANDLER_H

#include <algorithm>
#include <optional>
#include <string>

inline bool isOptionPresent(char **begin, char **end, const std::string &optionName) {
    return std::find(begin, end, optionName) != end;
}

template<typename T>
std::optional<T> getCMDLineOption(char **begin, char **end, const std::string &optionName) {
    char **itr = std::find(begin, end, optionName);
    if (!isOptionPresent(begin, end, optionName) || ++itr == end) {
        return {};
    }
    T parsed = dynamic_cast<T>(*itr);
    return parsed;
}


#endif //COMMANDLINEARGUMENTHANDLER_H
