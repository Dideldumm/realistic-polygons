//
// Created by dideldumm on 16.08.24.
//


#include <CGAL/draw_polygon_2.h>
#include "utils/PointGenerator/RandomPointGenerator.h"

#include "TwoOptMoves.h"

std::optional<Point> TwoOptMoves::getIntersection(const CgalTypes::Segment &edge, const CgalTypes::Segment &newPointEdge, const Point &oldEnd,
                                                  const Point &oldStart) {
    if (auto intersectEdgeToNewPoint = CGAL::intersection(edge, newPointEdge)) {
        // Determine the type of intersection using boost::get
        if (const Point *p = std::get_if<Point>(&*intersectEdgeToNewPoint)) {
            // Intersection is a point
            if (*p != oldEnd && *p != oldStart) {
                return {*p};
            }
        } else if (std::get_if<CgalTypes::Segment>(&*intersectEdgeToNewPoint)) {
            // Intersection is a line (lines are collinear)
            throw std::invalid_argument("The lines are collinear and overlap.");
        }
    }
    return {};
}

CgalTypes::Segment TwoOptMoves::findIntersection(const CgalTypes::Polygon &test, const Point &newPoint) {
    CgalTypes::Segment edgeToNewPoint;
    CgalTypes::Segment edgeFromNewPoint;
    Point oldStart;
    Point oldEnd;
    for (CgalTypes::Segment edge: test.edges()) {
        if (edge.end() == newPoint) {
            edgeToNewPoint = edge;
            oldStart = edge.start();
        }
        if (edge.start() == newPoint) {
            edgeFromNewPoint = edge;
            oldEnd = edge.end();
        }
    }

    for (CgalTypes::Segment edge: test.edges()) {
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

CgalTypes::Polygon TwoOptMoves::constructPolygonWithoutIntersection(const Point &point, CgalTypes::Polygon &test) const {
    const CgalTypes::Segment intersectingSegment = findIntersection(test, point);
    test = polygon;
    CgalTypes::Polygon newPolygon;
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

    CgalTypes::Polygon test = polygon;
    test.push_back(point);

    while (!test.is_simple()) {
        std::cout << "now" << std::endl;
        // CGAL::draw(test);
        test = constructPolygonWithoutIntersection(point, test);
    }
    polygon = test;
}
