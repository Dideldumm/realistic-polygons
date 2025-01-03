//
// Created by dideldumm on 23.08.24.
//

#ifndef TOSTRINGUTILS_H
#define TOSTRINGUTILS_H

#include <string>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Polygon_2.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel Kernel;
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

/**
 * Builds a string that represents the given point.
 * The string will look like this: a|b
 * @param point the point
 * @return a string reporesentation of the given point
 */
std::string pointToString(Point point);

/**
 * Builds a string that represents the given segment.
 * The string will look like this: [start_point, end_point]
 * @param segment the segment to represent
 * @return a string representation of the given segment
 */
std::string segmentToString(const Segment &segment);

std::string polygonToString(const Polygon &polygon);

#endif //TOSTRINGUTILS_H
