//
// Created by dideldumm on 12.07.24.
//
#include "AlgoGeoUtils.h"

inline bool is_left_of(const Point &a, const Point &b) {
    return a.x() < b.x();
}

inline bool is_right_of(const Point &a, const Point &b) {
    return a.x() > b.x();
}

inline bool is_above(const Point &p, const Segment &s) {
    return CGAL::left_turn(s[0], s[1], p);
}

inline bool is_below(const Point &p, const Segment &s) {
    return CGAL::right_turn(s[0], s[1], p);
}

bool LeftComparator::operator()(const Point &a, const Point &b) const {
    return is_left_of(a, b);
}

bool ::RightComparator::operator()(const Point &a, const Point &b) const {
    return is_right_of(a, b);
}