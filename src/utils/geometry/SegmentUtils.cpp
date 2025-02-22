//
// Created by dideldumm on 05.01.25.
//
#include "SegmentUtils.h"

bool is_left_of(const CgalTypes::Point &p, const CgalTypes::Segment &s) {
    return is_above(p, s);
}

bool is_right_of(const CgalTypes::Point &p, const CgalTypes::Segment &s) {
    return is_below(p, s);
}

bool is_above(const CgalTypes::Point &p, const CgalTypes::Segment &s) {
    return CGAL::left_turn(s[0], s[1], p);
}

bool is_below(const CgalTypes::Point &p, const CgalTypes::Segment &s) {
    return CGAL::right_turn(s[0], s[1], p);
}
