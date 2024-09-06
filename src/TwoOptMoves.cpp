//
// Created by dideldumm on 16.08.24.
//

#include <CGAL/draw_polygon_2.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Polygon_2.h>
#include "utils/AlgoGeoUtils.h"
#include "utils/RandomPointGenerator.h"
#include "utils/ToStringUtils.h"


typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef CGAL::Point_2<Kernel> Point;
typedef CGAL::Polygon_2<Kernel> Polygon;
typedef CGAL::Segment_2<Kernel> Segment;
typedef boost::variant<Point, Segment> IntersectionResult;

std::pair<Segment, Segment> swapSegments(const Segment &x, const Segment &y);

std::pair<Segment, Segment> swapSegmentsOtherWay(const Segment &x, const Segment &y);

class TwoOptMoves {
private:
    Polygon polygon;

    static Segment findIntersection(const Polygon &test, const Point &newPoint) {
        Segment newSegment1;
        Segment newSegment2;
        Point oldStart;
        Point oldEnd;
        for (Segment edge: test.edges()) {
            if (edge.end() == newPoint) {
                newSegment1 = edge;
                oldStart = edge.start();
            }
            if (edge.start() == newPoint) {
                newSegment2 = edge;
                oldEnd = edge.end();
            }
        }

        for (Segment edge: test.edges()) {
            if (edge == newSegment1 || edge == newSegment2) {
                continue;
            }

            if (auto intersection1 = CGAL::intersection(edge, newSegment1)) {
                // Determine the type of intersection using boost::get
                if (const Point* p = boost::get<Point>(&*intersection1)) {
                    // Intersection is a point
                    if (*p != oldEnd && *p != oldStart) {
                        return edge;
                    }
                } else if (boost::get<Segment>(&*intersection1)) {
                    // Intersection is a line (lines are collinear)
                    throw std::invalid_argument("The lines are collinear and overlap.");
                }
            } else if (auto intersection2 = CGAL::intersection(edge, newSegment2)) {
                // Determine the type of intersection using boost::get
                if (const Point* p = boost::get<Point>(&*intersection2)) {
                    // Intersection is a point
                    if (*p != oldEnd && *p != oldStart) {
                        return edge;
                    }
                } else if (boost::get<Segment>(&*intersection2)) {
                    // Intersection is a line (lines are collinear)
                    throw std::invalid_argument("The lines are collinear and overlap.");
                }
            }
        }
        throw std::invalid_argument("Iterated over all edges but found no intersection");
    }

public:
    void addPoint(const Point &point) {
        if (polygon.size() < 3) {
            polygon.push_back(point);
            return;
        }

        Polygon test = polygon;
        test.push_back(point);

        while (!test.is_simple()) {
            CGAL::draw(polygon);
            CGAL::draw(test);
            Segment intersectingSegment = findIntersection(test, point);
            test = polygon;
            for (auto it = test.begin(); it != test.end(); ++it) {
                if (const Point vertex = *it; vertex == intersectingSegment.end()) {
                    test.insert(it, point);
                    break;
                }
            }
            CGAL::draw(test);
        }
        polygon = test;
    }

    [[nodiscard]] Polygon getPolygon() const {
        return this->polygon;
    }
};

std::pair<Segment, Segment> swapSegments(const Segment &x, const Segment &y) {
    const Point a = x.start();
    const Point b = x.end();
    const Point c = y.start();
    const Point d = y.end();

    const Segment newX(a, c);
    const Segment newY(b, d);
    return {newX, newY};
}

std::pair<Segment, Segment> swapSegmentsOtherWay(const Segment &x, const Segment &y) {
    const Point a = x.start();
    const Point b = x.end();
    const Point c = y.start();
    const Point d = y.end();

    const Segment newX(a, d);
    const Segment newY(b, c);
    return {newX, newY};
}


int main() {
    // RandomPointGenerator point_generator(30.0);
    // std::vector<Point> points = point_generator.generatePoints(8);
    std::vector<Point> points = {{0, 0}, {0, -1}, {1, 1}, {2, -1}, {2, 0}};
    TwoOptMoves two_opt_moves;
    for (Point point: points) {
        two_opt_moves.addPoint(point);
    }
    const Polygon polygon = two_opt_moves.getPolygon();
    std::cout << "Edges: \n" << containerToString<Segment>(polygon.edges(), segmentToString, "\n") << std::endl;
    std::cout << "Number of edges: " << polygon.edges().size() << "\n" << std::endl;
    std::cout << "Vertices: \n" << containerToString<Point>(polygon.vertices(), pointToString, "\n") << std::endl;
    std::cout << "Number of vertices: " << polygon.size() << "\n" << std::endl;
}
