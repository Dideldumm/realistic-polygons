//
// Created by dideldumm on 16.08.24.
//


#include <CGAL/draw_polygon_2.h>
#include "utils/PointGenerator/RandomPointGenerator.h"
#include "utils/CommandLineArgumentHandler.h"

#include "TwoOptMoves.h"


typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef CGAL::Point_2<Kernel> Point;
typedef CGAL::Polygon_2<Kernel> Polygon;
typedef CGAL::Segment_2<Kernel> Segment;


std::optional<Point> TwoOptMoves::getIntersection(const Segment &edge, const Segment &newPointEdge, const Point &oldEnd,
                                                  const Point &oldStart) {
    if (auto intersectEdgeToNewPoint = CGAL::intersection(edge, newPointEdge)) {
        // Determine the type of intersection using boost::get
        if (const Point *p = std::get_if<Point>(&*intersectEdgeToNewPoint)) {
            // Intersection is a point
            if (*p != oldEnd && *p != oldStart) {
                return {*p};
            }
        } else if (std::get_if<Segment>(&*intersectEdgeToNewPoint)) {
            // Intersection is a line (lines are collinear)
            throw std::invalid_argument("The lines are collinear and overlap.");
        }
    }
    return {};
}

Segment TwoOptMoves::findIntersection(const Polygon &test, const Point &newPoint) {
    Segment edgeToNewPoint;
    Segment edgeFromNewPoint;
    Point oldStart;
    Point oldEnd;
    for (Segment edge: test.edges()) {
        if (edge.end() == newPoint) {
            edgeToNewPoint = edge;
            oldStart = edge.start();
        }
        if (edge.start() == newPoint) {
            edgeFromNewPoint = edge;
            oldEnd = edge.end();
        }
    }

    for (Segment edge: test.edges()) {
        if (edge == edgeToNewPoint || edge == edgeFromNewPoint) {
            // skip the added segments since they obviously intersect with themselves
            continue;
        }

        std::optional<Point> intersectionWithNewEdges = getIntersection(
            edge, edgeToNewPoint, oldEnd, oldStart);
        if (intersectionWithNewEdges) {
            return edge;
        }

        intersectionWithNewEdges = getIntersection(edge, edgeFromNewPoint, oldEnd, oldStart);
        if (intersectionWithNewEdges) {
            return edge;
        }
    }
    throw std::invalid_argument("Iterated over all edges but found no intersection");
}

// Polygon TwoOptMoves::constructPolygonWithoutIntersection(const Point &point, Polygon &test) const {
//     const Segment intersectingSegment = findIntersection(test, point);
//     test = polygon;
//     for (auto it = test.begin(); it != test.end(); ++it) {
//         if (const Point vertex = *it; vertex == intersectingSegment.end()) {
//             test.insert(it, point);
//             break;
//         }
//     }
//     return test;
// }

Polygon TwoOptMoves::constructPolygonWithoutIntersection(const Point &point, Polygon &test) const {
    const Segment intersectingSegment = findIntersection(test, point);
    test = polygon;
    Polygon newPolygon;
    bool alreadyAdded = false;
    for (Point vertex: test.vertices()) {
        newPolygon.push_back(vertex);
        if (!alreadyAdded && (vertex == intersectingSegment.start() || vertex == intersectingSegment.end())) {
            newPolygon.push_back(point);
            alreadyAdded = true;
        }
    }
    return newPolygon;
}

void TwoOptMoves::addPoint(const Point &point) {
    if (polygon.size() < 3) {
        // trivial case
        polygon.push_back(point);
        return;
    }

    Polygon test = polygon;
    test.push_back(point);

    while (!test.is_simple()) {
        std::cout << "now" << std::endl;
        CGAL::draw(test);
        test = constructPolygonWithoutIntersection(point, test);
    }
    polygon = test;
}
