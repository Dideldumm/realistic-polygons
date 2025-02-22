//
// Created by dideldumm on 12.09.24.
//

#ifndef TWOOPTMOVES_H
#define TWOOPTMOVES_H

#include "utils/geometry/CgalTypes.h"

class TwoOptMoves {
    CgalTypes::Polygon polygon;

    static std::optional<Point> getIntersection(const CgalTypes::Segment &edge, const CgalTypes::Segment &newPointEdge, const Point &oldEnd,
                                                const Point &oldStart);

    static CgalTypes::Segment findIntersection(const CgalTypes::Polygon &test, const Point &newPoint);

    [[nodiscard]] CgalTypes::Polygon constructPolygonWithoutIntersection(const Point &point, CgalTypes::Polygon &test) const;

public:
    void addPoint(const Point &point);

    [[nodiscard]] CgalTypes::Polygon getPolygon() const {
        return this->polygon;
    }
};

#endif //TWOOPTMOVES_H
