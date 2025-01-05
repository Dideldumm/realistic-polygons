//
// Created by dideldumm on 05.01.25.
//

#ifndef SEGMENTUTILS_H
#define SEGMENTUTILS_H

#include <CGAL/Exact_predicates_exact_constructions_kernel.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel Kernel;
typedef CGAL::Point_2<Kernel> Point;
typedef CGAL::Segment_2<Kernel> Segment;

bool is_left_of(const Point &p, const Segment &s);

bool is_right_of(const Point &p, const Segment &s);

bool is_above(const Point &p, const Segment &s);

bool is_below(const Point &p, const Segment &s);

template<typename T>
Segment find_nearest_segment(const T &segments, const Point &point) {
    auto it = segments.begin();
    auto minimal_distance = CGAL::squared_distance(*it, point);
    Segment nearest_segment = *it;
    for (++it; it != segments.end(); ++it) {
        Segment segment = *it;
        if (const auto distance = CGAL::squared_distance(segment, point); distance < minimal_distance) {
            minimal_distance = distance;
            nearest_segment = segment;
        }
    }
    return nearest_segment;
}


#endif //SEGMENTUTILS_H
