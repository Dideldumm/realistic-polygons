//
// Created by dideldumm on 11.07.24.
//

#ifndef ALGOGEOUTILS_H
#define ALGOGEOUTILS_H

#include <CGAL/Exact_predicates_exact_constructions_kernel.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel Kernel;
typedef CGAL::Point_2<Kernel> Point;
typedef CGAL::Segment_2<Kernel> Segment;

bool is_left_of(const Point &a, const Point &b);

bool is_right_of(const Point &a, const Point &b);

bool is_above(const Point &a, const Point &b);

bool is_below(const Point &a, const Point &b);

Point get_leftmost(const std::vector<Point> &points);

Point get_rightmost(const std::vector<Point> &points);

Point get_topmost(const std::vector<Point> &points);

Point get_bottommost(const std::vector<Point> &points);


#endif //ALGOGEOUTILS_H
