//
// Created by dideldumm on 12.09.24.
//

#ifndef TWOOPTMOVES_H
#define TWOOPTMOVES_H

#include "utils/geometry/CgalTypes.h"

class TwoOptMoves {
    CgalTypes::Polygon polygon;

    static std::optional<CgalTypes::Point> getIntersection(const CgalTypes::Segment &edge,
                                                           const CgalTypes::Segment &newPointEdge,
                                                           const CgalTypes::Point &oldEnd,
                                                           const CgalTypes::Point &oldStart);

    static CgalTypes::Segment findIntersection(const CgalTypes::Polygon &test, const CgalTypes::Point &newPoint);

    [[nodiscard]] CgalTypes::Polygon constructPolygonWithoutIntersection(
        const CgalTypes::Point &point, CgalTypes::Polygon &test) const;

public:
    void addPoint(const CgalTypes::Point &point);

    [[nodiscard]] CgalTypes::Polygon getPolygon() const {
        return this->polygon;
    }
};

#endif //TWOOPTMOVES_H
