//
// Created by dideldumm on 16.07.24.
//

#include "CommandLineArgumentHandler.h"
#include <regex>

std::optional<std::string> getCMDLineOption(char **begin, char **end, const std::string &optionName) {
    char **itr = std::find(begin, end, optionName);
    if (!isOptionPresent(begin, end, optionName) || ++itr == end) {
        return {};
    }
    return *itr;
}

std::string getMandatoryCMDLineOption(char **begin, char **end, const std::string &optionName) {
    std::optional<std::string> maybeOption = getCMDLineOption(begin, end, optionName);
    if (!maybeOption.has_value()) {
        throw std::invalid_argument("No value for option " + optionName + " was provided!");
    }
    return maybeOption.value();
}


Point parsePoint(const std::string &pointString) {
    const std::regex numberRegex("\\d+");
    std::smatch numberMatch;
    std::regex_search(pointString, numberMatch, numberRegex);
    std::regex_search(pointString, numberMatch, numberRegex);

    if (numberMatch.length() < 2) {
        throw std::invalid_argument("could'nt find 2 numbers in point string: " + pointString);
    }

    const int x = std::stoi(numberMatch[0]);
    const int y = std::stoi(numberMatch[1]);
    return {x, y};
}
