//
// Created by dideldumm on 05.01.25.
//

#include "QuadrantTree.h"
#include "../utils/geometry/PointUtils.h"
#include "../utils/geometry/SegmentUtils.h"

QuadrantTree::QuadrantTree(const std::vector<Point> &points) {
    if (points.size() <= 3) {
        this->points = points;
        this->bottom_left = nullptr;
        this->bottom_right = nullptr;
        this->top_left = nullptr;
        this->top_right = nullptr;
        return;
    }

    std::vector<Point> top_left_points;
    std::vector<Point> top_right_points;
    std::vector<Point> bottom_left_points;
    std::vector<Point> bottom_right_points;
    const Point leftmost = get_leftmost(points);
    const Point rightmost = get_rightmost(points);
    const Segment left_to_right(leftmost, rightmost);
    const Point topmost = get_topmost(points);
    const Point bottommost = get_bottommost(points);
    const Segment top_to_bottom(topmost, bottommost);

    for (const Point &p: points) {
        if (is_above(p, left_to_right)) {
            if (is_left_of(p, top_to_bottom)) {
                top_left_points.emplace_back(p);
            } else {
                top_right_points.emplace_back(p);
            }
        } else {
            if (is_left_of(p, top_to_bottom)) {
                bottom_left_points.emplace_back(p);
            } else {
                bottom_right_points.emplace_back(p);
            }
        }
    }
    this->top_left(top_left_points);
    this->top_right(top_right_points);
    this->bottom_left(bottom_left_points);
    this->bottom_right(bottom_right_points);
    this->points = {leftmost, rightmost, topmost, bottommost};
}

bool QuadrantTree::is_leaf() const {
    return this->bottom_left == nullptr && this->bottom_right == nullptr && this->top_left == nullptr && this->top_right
           == nullptr;
}
