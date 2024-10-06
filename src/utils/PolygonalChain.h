//
// Created by dideldumm on 06.10.24.
//

#ifndef POLYGONALCHAIN_H
#define POLYGONALCHAIN_H

#include <CGAL/draw_polygon_2.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Polygon_2.h>

#include <ranges>
#include "ToStringUtils.h"

typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef CGAL::Point_2<Kernel> Point;
typedef CGAL::Polygon_2<Kernel> Polygon;

class PolygonalChain {
private:
    std::vector<Point> elements;

    void addAllElements(bool forwards, const std::vector<Point> &elements);

public:
    explicit PolygonalChain() = default;

    explicit PolygonalChain(Point p) {
        elements = {p};
    }

    explicit PolygonalChain(const PolygonalChain &a, const PolygonalChain &b);

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

    bool operator==(const PolygonalChain &other) const {
        return other.elements == this->elements;
    }
};



#endif //POLYGONALCHAIN_H
