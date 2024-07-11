//
// Created by dideldumm on 11.07.24.
//

#ifndef ALGOGEOUTILS_H
#define ALGOGEOUTILS_H

#include <CGAL/Exact_predicates_exact_constructions_kernel.h>


typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef CGAL::Point_2<Kernel> Point;
typedef CGAL::Segment_2<Kernel> Segment;

inline bool is_left_of(const Point& a, const Point& b) {
    return a.x() < b.x();
}

inline bool is_right_of(const Point& a, const Point& b) {
    return a.x() > b.x();
}

inline bool is_above(const Point& p, const Segment& s) {
    return CGAL::left_turn(s[0], s[1], p);
}

inline bool is_below(const Point& p, const Segment& s) {
    return CGAL::right_turn(s[0], s[1], p);
}

struct LeftComparator {
    bool operator() (const Point& a,const Point& b) const {
        return is_left_of(a, b);
    }
};

struct RightComparator {
    bool operator() (const Point& a,const Point& b) const {
        return is_right_of(a, b);
    }
};

#endif //ALGOGEOUTILS_H
