//
// Created by dideldumm on 23.08.24.
//

#ifndef TOSTRINGUTILS_H
#define TOSTRINGUTILS_H

#include <string>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Polygon_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef CGAL::Point_2<Kernel> Point;
typedef CGAL::Segment_2<Kernel> Segment;
typedef CGAL::Polygon_2<Kernel> Polygon;


template<class T>
std::string containerToString(const auto &container, auto toString, auto delimiter) {
    std::stringstream stringStream;
    stringStream << "[";
    for (const T &element: container) {
        stringStream << toString(element) << delimiter;
    }
    stringStream << "]";
    return stringStream.str();
}

template<class T>
std::string containerToString(const auto &container, auto toString) {
    return containerToString<T>(container, toString, ", ");
}

std::string pointToString(Point point);

std::string segmentToString(const Segment &segment);

std::string polygonToString(const Polygon &polygon);

#endif //TOSTRINGUTILS_H
