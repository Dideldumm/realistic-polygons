//
// Created by dideldumm on 12.09.24.
//

#ifndef TWOOPTMOVES_H
#define TWOOPTMOVES_H

#include <CGAL/Polygon_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef CGAL::Point_2<Kernel> Point;
typedef CGAL::Polygon_2<Kernel> Polygon;
typedef CGAL::Segment_2<Kernel> Segment;

class TwoOptMoves {
    Polygon polygon;

    static std::optional<Point> getIntersection(const Segment &edge, const Segment &newPointEdge, const Point &oldEnd,
                                                const Point &oldStart);

    static Segment findIntersection(const Polygon &test, const Point &newPoint);

public:
    void addPoint(const Point &point);

    [[nodiscard]] Polygon getPolygon() const {
        return this->polygon;
    }

    static int main(int argc, char **argv);
};

#endif //TWOOPTMOVES_H
