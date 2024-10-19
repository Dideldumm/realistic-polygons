//
// Created by dideldumm on 19.10.24.
//


#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/convex_hull_2.h>
#include "utils/ToStringUtils.h"

typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef CGAL::Point_2<Kernel> Point;
typedef CGAL::Segment_2<Kernel> Segment;
typedef CGAL::Polygon_2<Kernel> Polygon;


int main() {
    const Polygon polygon;
    const std::string string = containerToString<Segment>(polygon.edges(), segmentToString, "\n");
    std::cout << string << std::endl;
}
