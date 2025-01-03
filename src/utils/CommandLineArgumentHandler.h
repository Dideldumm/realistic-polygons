//
// Created by dideldumm on 13.07.24.
//

#ifndef COMMANDLINEARGUMENTHANDLER_H
#define COMMANDLINEARGUMENTHANDLER_H

#include <algorithm>
#include <optional>
#include <string>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Polygon_2.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel Kernel;
typedef CGAL::Polygon_2<Kernel> Polygon;
typedef CGAL::Point_2<Kernel> Point;

inline bool isOptionPresent(char **begin, char **end, const std::string &optionName) {
    return std::find(begin, end, optionName) != end;
}

Point parsePoint(const std::string &pointString);

std::optional<std::string> getCMDLineOption(char **begin, char **end, const std::string &optionName);

std::string getMandatoryCMDLineOption(char **begin, char **end, const std::string &optionName);


#endif //COMMANDLINEARGUMENTHANDLER_H
