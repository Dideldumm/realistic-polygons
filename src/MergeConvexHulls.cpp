//
// Created by dideldumm on 19.09.24.
//

#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/convex_hull_2.h>
#include <CGAL/draw_polygon_2.h>

#include "utils/geometry/PointAndSegmentUtils.h"
#include "utils/geometry/PolygonUtils.h"
#include "utils/RandomPointGenerator.h"

typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef CGAL::Point_2<Kernel> Point;
typedef CGAL::Segment_2<Kernel> Segment;
typedef CGAL::Polygon_2<Kernel> Polygon;
typedef std::list<Point> ConvexHull;


ConvexHull create_convex_hull(const std::list<Point> &vertices) {
    ConvexHull new_hull;
    CGAL::convex_hull_2(vertices.begin(), vertices.end(), std::back_inserter(new_hull));
    return new_hull;
}

std::list<ConvexHull> build_convex_hulls(std::list<Point> points) {
    std::list<ConvexHull> convex_hulls;
    while (!points.empty()) {
        const ConvexHull new_hull = create_convex_hull(points);
        convex_hulls.emplace_back(new_hull);
        for (Point point: new_hull) {
            points.remove(point);
        }
    }
    return convex_hulls;
}

void merge(Polygon &polygon, const ConvexHull &new_hull) {
    for (Point point: new_hull) {
        const Segment nearest_segment = find_nearest_segment(polygon.edges(), point);
        insert_point_at_segment(polygon, nearest_segment, point);
    }
}

Polygon merge_convex_hulls_algorithm(const std::list<Point> &vertices) {
    std::list<ConvexHull> convex_hulls = build_convex_hulls(vertices);
    if (convex_hulls.empty()) {
        std::cout << "Houston wir haben ein Problem!" << std::endl;
    }
    ConvexHull initial_hull = convex_hulls.front();
    convex_hulls.pop_front();
    Polygon polygon(initial_hull.begin(), initial_hull.end());
    while (!convex_hulls.empty()) {
        ConvexHull new_hull = convex_hulls.front();
        convex_hulls.pop_front();
        merge(polygon, new_hull);
    }
    return polygon;
}

int main() {
    RandomPointGenerator point_generator{};
    std::list<Point> points;
    std::ranges::copy(point_generator.generatePoints(1032), std::back_inserter(points));
    const Polygon polygon = merge_convex_hulls_algorithm(points);
    CGAL::draw(polygon);
}
