//
// Created by dideldumm on 06.10.24.
//

#ifndef POLYGONALCHAIN_H
#define POLYGONALCHAIN_H

#include <CGAL/draw_polygon_2.h>

#include "../ToStringUtils.h"

class PolygonalChain {
private:
    std::vector<CgalTypes::Point> elements;

    void addAllElements(bool forwards, const std::vector<CgalTypes::Point> &elements);

public:
    explicit PolygonalChain(): elements({}) {
    };

    /**
     * Creates a Polygonal Chain that contains exactly one point
     * @param p the point that this polygonal chain will contain
     */
    explicit PolygonalChain(CgalTypes::Point p) {
        elements = {p};
    }

    /**
     * Creates a longer Polygonal Chain by merging a and b.
     * The chains a and b will be merged at their nearest segments.
     * @param a a polygonal chain
     * @param b another polygonal chain
     */
    explicit PolygonalChain(const PolygonalChain &a, const PolygonalChain &b);


    /**
     * Creates a new Polygonal Chain by inserting the given point into the given chain.
     * The point will be inserted at the segment that is nearest to the point.
     * @param chain the polygonal chain, where the point is inserted
     * @param point the point to be inserted
     */
    explicit PolygonalChain(const PolygonalChain &chain, const CgalTypes::Point &point);

    [[nodiscard]] CgalTypes::Point getLastElement() const {
        return elements.back();
    }

    [[nodiscard]] CgalTypes::Point getFirstElement() const {
        return elements.front();
    }

    [[nodiscard]] std::string toString() const {
        return polygonToString(CgalTypes::Polygon(elements.begin(), elements.end()));
    }

    [[nodiscard]] std::vector<CgalTypes::Point> getElements() const {
        return elements;
    };

    [[nodiscard]] size_t size() const {
        return elements.size();
    }

    bool operator==(const PolygonalChain &other) const {
        return other.elements == this->elements;
    }

    static auto find_minimal_squared_distance(const CgalTypes::Point &a, const PolygonalChain &b);

    static auto find_minimal_squared_distance(const PolygonalChain &a, const PolygonalChain &b);
};

#endif //POLYGONALCHAIN_H
