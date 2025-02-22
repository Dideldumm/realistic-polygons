//
// Created by dideldumm on 23.08.24.
//

#include "ToStringUtils.h"

std::string pointToString(const CgalTypes::Point &point) {
    const std::string x = std::to_string(CGAL::to_double(point.x()));
    const std::string y = std::to_string(CGAL::to_double(point.y()));
    return x + "|" + y;
}

std::string segmentToString(const CgalTypes::Segment &segment) {
    const auto x = segment.start();
    const auto y = segment.end();
    return containerToString<CgalTypes::Point>(std::vector{x, y}, pointToString);
}

std::string polygonToString(const CgalTypes::Polygon &polygon) {
    return containerToString<CgalTypes::Point>(polygon.vertices(), pointToString);
}
