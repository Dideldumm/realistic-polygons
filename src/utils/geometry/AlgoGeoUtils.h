//
// Created by dideldumm on 11.07.24.
//

#ifndef ALGOGEOUTILS_H
#define ALGOGEOUTILS_H

#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Polygon_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef CGAL::Point_2<Kernel> Point;
typedef CGAL::Segment_2<Kernel> Segment;
typedef CGAL::Polygon_2<Kernel> Polygon;

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

#endif //ALGOGEOUTILS_H
