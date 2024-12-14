//
// Created by dideldumm on 11.07.24.
//

#ifndef ALGOGEOUTILS_H
#define ALGOGEOUTILS_H

#include <CGAL/Exact_predicates_exact_constructions_kernel.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef CGAL::Point_2<Kernel> Point;
typedef CGAL::Segment_2<Kernel> Segment;

bool is_left_of(const Point &a, const Point &b);

bool is_right_of(const Point &a, const Point &b);

bool is_above(const Point &p, const Segment &s);

bool is_below(const Point &p, const Segment &s);

class LeftComparator {
public:
    bool operator()(const Point &a, const Point &b) const;
};

class RightComparator {
public:
    bool operator()(const Point &a, const Point &b) const;
};

template<typename T>
Segment find_nearest_segment(const T &segments, const Point &point) {
    double minimal_distance = std::numeric_limits<double>::max();
    Segment nearest_segment;
    for (const Segment &segment: segments) {
        if (const double distance = CGAL::squared_distance(segment, point); distance < minimal_distance) {
            minimal_distance = distance;
            nearest_segment = segment;
        }
    }
    return nearest_segment;
}



#endif //ALGOGEOUTILS_H
