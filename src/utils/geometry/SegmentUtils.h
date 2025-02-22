//
// Created by dideldumm on 05.01.25.
//

#ifndef SEGMENTUTILS_H
#define SEGMENTUTILS_H

#include "CgalTypes.h"

bool is_left_of(const CgalTypes::Point &p, const CgalTypes::Segment &s);

bool is_right_of(const CgalTypes::Point &p, const CgalTypes::Segment &s);

bool is_above(const CgalTypes::Point &p, const CgalTypes::Segment &s);

bool is_below(const CgalTypes::Point &p, const CgalTypes::Segment &s);

template<typename T>
CgalTypes::Segment find_nearest_segment(const T &segments, const CgalTypes::Point &point) {
    auto it = segments.begin();
    auto minimal_distance = CGAL::squared_distance(*it, point);
    CgalTypes::Segment nearest_segment = *it;
    for (++it; it != segments.end(); ++it) {
        CgalTypes::Segment segment = *it;
        if (const auto distance = CGAL::squared_distance(segment, point); distance < minimal_distance) {
            minimal_distance = distance;
            nearest_segment = segment;
        }
    }
    return nearest_segment;
}


#endif //SEGMENTUTILS_H
