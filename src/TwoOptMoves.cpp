//
// Created by dideldumm on 16.08.24.
//


#include <CGAL/draw_polygon_2.h>
#include "utils/AlgoGeoUtils.h"
#include "utils/RandomPointGenerator.h"
#include "utils/ToStringUtils.h"
#include "utils/CommandLineArgumentHandler.h"

#include "TwoOptMoves.h"


typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef CGAL::Point_2<Kernel> Point;
typedef CGAL::Polygon_2<Kernel> Polygon;
typedef CGAL::Segment_2<Kernel> Segment;
typedef boost::variant<Point, Segment> IntersectionResult;


std::optional<Point> TwoOptMoves::getIntersection(const Segment &edge, const Segment &newPointEdge, const Point &oldEnd,
                                                  const Point &oldStart) {
    if (auto intersectEdgeToNewPoint = CGAL::intersection(edge, newPointEdge)) {
        // Determine the type of intersection using boost::get
        if (const Point *p = boost::get<Point>(&*intersectEdgeToNewPoint)) {
            // Intersection is a point
            if (*p != oldEnd && *p != oldStart) {
                return {*p};
            }
        } else if (boost::get<Segment>(&*intersectEdgeToNewPoint)) {
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

void TwoOptMoves::addPoint(const Point &point) {
    if (polygon.size() < 3) {
        polygon.push_back(point);
        return;
    }

    Polygon test = polygon;
    test.push_back(point);

    while (!test.is_simple()) {
        Segment intersectingSegment = findIntersection(test, point);
        test = polygon;
        for (auto it = test.begin(); it != test.end(); ++it) {
            if (const Point vertex = *it; vertex == intersectingSegment.end()) {
                test.insert(it, point);
                break;
            }
        }
    }
    polygon = test;
}

int TwoOptMoves::main(const int argc, char **argv) {
    const int numberOfPoints = argc > 0 ? std::stoi(argv[0]) : 12;

    RandomPointGenerator point_generator(30.0);
    std::vector<Point> points = point_generator.generatePoints(numberOfPoints);
    TwoOptMoves two_opt_moves;
    for (Point point: points) {
        two_opt_moves.addPoint(point);
    }
    const Polygon polygon = two_opt_moves.getPolygon();
    std::cout << "Edges: \n" << containerToString<Segment>(polygon.edges(), segmentToString, "\n") << std::endl;
    std::cout << "Number of edges: " << polygon.edges().size() << "\n" << std::endl;
    std::cout << "Vertices: \n" << containerToString<Point>(polygon.vertices(), pointToString, "\n") << std::endl;
    std::cout << "Number of vertices: " << polygon.size() << "\n" << std::endl;
    CGAL::draw(polygon);
    return 0;
}
