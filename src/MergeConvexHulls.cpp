//
// Created by dideldumm on 19.09.24.
//

#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/convex_hull_2.h>

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
    // TODO implement
    // Wir wollen am liebsten die Punkte von new_hull durchgehen und
    // an der Kante von polygon einfügen, die den Punkt am nächsten ist.
    // Dafür brauchen wir eine Methode, die uns einen Punkt an einer Kante einfügen lässt.
    // Polygon.insert fügt vor i ein, das heißt wir nehmen den Endpunkt der Kante??
}

Polygon merge_convex_hulls_algorithm(const auto &vertices) {
    std::list<ConvexHull> convex_hulls = build_convex_hulls(vertices);
    if (convex_hulls.empty()) {
        std::cout << "Houston wir haben ein Problem!" << std::endl;
    }
    ConvexHull initial_hull = convex_hulls.front();
    Polygon polygon(initial_hull.begin(), initial_hull.end());
    convex_hulls.pop_front();
    while (!convex_hulls.empty()) {
        ConvexHull new_hull = convex_hulls.front();
        convex_hulls.pop_front();
        merge(polygon, new_hull);
    }
    return polygon;
}

int main() {
}
