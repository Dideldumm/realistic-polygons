//
// Created by dideldumm on 19.10.24.
//


#include <CGAL/Polygon_2.h>
#include <CGAL/Boolean_set_operations_2.h>
#include <CGAL/draw_polygon_2.h>

#include "./utils/ToStringUtils.h"

typedef CGAL::Exact_predicates_exact_constructions_kernel Kernel;
typedef CGAL::Point_2<Kernel> Point;
typedef CGAL::Segment_2<Kernel> Segment;
typedef CGAL::Polygon_2<Kernel> Polygon;
typedef CGAL::Polygon_with_holes_2<Kernel> PolygonWithHoles;

void println(const std::string &s) {
    std::cout << s << std::endl;
}

int main() {

}
