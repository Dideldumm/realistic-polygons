//
// Created by dideldumm on 12.07.24.
//
#include "PointUtils.h"

bool is_left_of(const Point &a, const Point &b) {
    return a.x() < b.x() || (a.x() == b.x() && a.y() < b.y());
}

bool is_right_of(const Point &a, const Point &b) {
    return a.x() > b.x() || (a.x() == b.x() && a.y() > b.y());
}

bool is_below(const Point &a, const Point &b) {
    return a.y() < b.y() || (a.y() == b.y() && a.x() < b.x());
}

bool is_above(const Point &a, const Point &b) {
    return a.y() > b.y() || (a.y() == b.y() && a.x() > b.x());
}

Point leftmost(const std::vector<Point> &points) {
    return *std::ranges::max_element(points, is_left_of);
}

Point rightmost(const std::vector<Point> &points) {
    return *std::ranges::max_element(points, is_right_of);
}

Point topmost(const std::vector<Point> &points) {
    return *std::ranges::max_element(points, is_above);
}

Point bottommost(const std::vector<Point> &points) {
    return *std::ranges::max_element(points, is_below);
}
