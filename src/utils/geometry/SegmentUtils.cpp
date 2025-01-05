//
// Created by dideldumm on 05.01.25.
//
#include "SegmentUtils.h"

bool is_above(const Point &p, const Segment &s) {
    return CGAL::left_turn(s[0], s[1], p);
}

bool is_below(const Point &p, const Segment &s) {
    return CGAL::right_turn(s[0], s[1], p);
