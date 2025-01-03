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

void print(const std::string &s) {
    std::cout << s << std::endl;
}

int main() {
    std::vector<Point> points{{0, 0}, {3, 0}, {2, 1}, {1, 1}};
    std::vector<Point> other_points{{1.2, 3}, {1.1, 0.8}, {2.5, 3.2}};

    const Polygon polygon(points.begin(), points.end());
    CGAL::draw(polygon);
    const Polygon other_polygon(other_points.begin(), other_points.end());
    CGAL::draw(other_polygon);
    PolygonWithHoles joined_polygon;
    const bool overlap = CGAL::join(polygon, other_polygon, joined_polygon);

    print("Overlap = " + overlap);

    print("Joined Outer Boundary: ");
    print(polygonToString(joined_polygon.outer_boundary()));
    CGAL::draw(joined_polygon.outer_boundary());
}
