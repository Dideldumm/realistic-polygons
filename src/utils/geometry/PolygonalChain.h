//
// Created by dideldumm on 06.10.24.
//

#ifndef POLYGONALCHAIN_H
#define POLYGONALCHAIN_H

#include <CGAL/draw_polygon_2.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Polygon_2.h>

#include <ranges>
#include "../ToStringUtils.h"

typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef CGAL::Point_2<Kernel> Point;
typedef CGAL::Polygon_2<Kernel> Polygon;

class PolygonalChain {
private:
    std::vector<Point> elements;

    void addAllElements(bool forwards, const std::vector<Point> &elements);

public:
    /**
     * Creates a Polygonal Chain that contains exactly one point
     * @param p the point that this polygonal chain will contain
     */
    explicit PolygonalChain(Point p) {
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
    explicit PolygonalChain(const PolygonalChain &chain, const Point &point);

    [[nodiscard]] Point getLastElement() const {
        return elements.back();
    }

    [[nodiscard]] Point getFirstElement() const {
        return elements.front();
    }

    [[nodiscard]] std::string toString() const {
        return polygonToString(Polygon(elements.begin(), elements.end()));
    }

    [[nodiscard]] std::vector<Point> getElements() const {
        return elements;
    };

    [[nodiscard]] size_t size() const {
        return elements.size();
    }

    bool operator==(const PolygonalChain &other) const {
        return other.elements == this->elements;
    }
};



#endif //POLYGONALCHAIN_H
