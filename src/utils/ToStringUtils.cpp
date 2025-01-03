//
// Created by dideldumm on 23.08.24.
//

#include "ToStringUtils.h"

std::string pointToString(const Point &point) {
    const std::string x = std::to_string(CGAL::to_double(point.x()));
    const std::string y = std::to_string(CGAL::to_double(point.y()));
    return x + "|" + y;
}

std::string segmentToString(const Segment &segment) {
    const auto x = segment.start();
    const auto y = segment.end();
    return containerToString<Point>(std::vector{x, y}, pointToString);
}

std::string polygonToString(const Polygon &polygon) {
    return containerToString<Point>(polygon.vertices(), pointToString);
}
