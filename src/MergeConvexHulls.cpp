//
// Created by dideldumm on 19.09.24.
//

#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/convex_hull_2.h>
#include "utils/VectorUtils.h"

typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef CGAL::Point_2<Kernel> Point;
typedef CGAL::Segment_2<Kernel> Segment;
typedef CGAL::Polygon_2<Kernel> Polygon;
typedef Polygon ConvexHull;


std::list<ConvexHull> build_convex_hulls(std::vector<Point> vertices) {
    std::list<ConvexHull> hulls;
    while (!vertices.empty()) {
        const ConvexHull new_hull;
        CGAL::convex_hull_2(vertices.begin(), vertices.end(), new_hull);
        hulls.emplace_back(new_hull);
        remove_all_from_vector(vertices, new_hull.vertices());
    }
    return hulls;
}

Polygon merge_convex_hulls(const auto &vertices) {
}

int main(int argc, char *argv[]) {
}
