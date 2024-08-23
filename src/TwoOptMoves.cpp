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

/*
class TwoOptMoves {
private:
    Polygon polygon;

    void fixThePolygon() {
        const unsigned int lastEdgeIndex = polygon.edges().size() - 1;
        Segment lastEdge = polygon.edge(lastEdgeIndex);
    }

public:

    void addPoint(const Point &point) {
        this->polygon.push_back(point);
        if (!this->polygon.is_simple()) {
            this->fixThePolygon();
        }
    }

    [[nodiscard]] Polygon getPolygon() const {
        return this->polygon;
    }
};
*/
int main() {
    RandomPointGenerator point_generator(30.0);
    std::vector<Point> points = point_generator.generatePoints(5);
    const Polygon polygon(points.begin(), points.end());
    std::cout << "Edges: \n" << containerToString<Segment>(polygon.edges(), segmentToString, "\n") << std::endl;
    std::cout << "Number of edges: " << polygon.edges().size() << "\n" << std::endl;
    std::cout << "Vertices: \n" << containerToString<Point>(polygon.vertices(), pointToString, "\n") << std::endl;
    std::cout << "Number of vertices: " << polygon.size() << "\n" << std::endl;
}
