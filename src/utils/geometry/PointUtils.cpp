//
// Created by dideldumm on 12.07.24.
//
#include "PointUtils.h"

bool is_left_of(const CgalTypes::Point &a, const CgalTypes::Point &b) {
    return a.x() < b.x() || (a.x() == b.x() && a.y() < b.y());
}

bool is_right_of(const CgalTypes::Point &a, const CgalTypes::Point &b) {
    return a.x() > b.x() || (a.x() == b.x() && a.y() > b.y());
}

bool is_below(const CgalTypes::Point &a, const CgalTypes::Point &b) {
    return a.y() < b.y() || (a.y() == b.y() && a.x() < b.x());
}

bool is_above(const CgalTypes::Point &a, const CgalTypes::Point &b) {
    return a.y() > b.y() || (a.y() == b.y() && a.x() > b.x());
}

CgalTypes::Point get_leftmost(const std::vector<CgalTypes::Point> &points) {
    return *std::ranges::max_element(points, is_left_of);
}

CgalTypes::Point get_rightmost(const std::vector<CgalTypes::Point> &points) {
    return *std::ranges::max_element(points, is_right_of);
}

CgalTypes::Point get_topmost(const std::vector<CgalTypes::Point> &points) {
    return *std::ranges::max_element(points, is_above);
}

CgalTypes::Point get_bottommost(const std::vector<CgalTypes::Point> &points) {
    return *std::ranges::max_element(points, is_below);
}
