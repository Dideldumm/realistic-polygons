//
// Created by dideldumm on 19.09.24.
//

#include <CGAL/draw_polygon_2.h>

#include "TwoOptMoves.h"
#include "utils/ToStringUtils.h"
#include "utils/geometry/CgalTypes.h"

int main(const int argc, char **argv) {
    const int numberOfPoints = argc > 1 ? std::stoi(argv[1]) : 12;

    CgalTypes::PointGenerator pointGenerator(1);
    std::vector<CgalTypes::Point> points;
    std::copy_n(pointGenerator, numberOfPoints, std::back_inserter(points));

    TwoOptMoves two_opt_moves;
    for (CgalTypes::Point point: points) {
        two_opt_moves.addPoint(point);
    }
    const CgalTypes::Polygon polygon = two_opt_moves.getPolygon();
    std::cout << "Edges: \n" << containerToString<CgalTypes::Segment>(polygon.edges(), segmentToString, "\n") <<
            std::endl;
    std::cout << "Number of edges: " << polygon.edges().size() << "\n" << std::endl;
    std::cout << "Vertices: \n" << containerToString<CgalTypes::Point>(polygon.vertices(), pointToString, "\n") <<
            std::endl;
    std::cout << "Number of vertices: " << polygon.size() << "\n" << std::endl;
    CGAL::draw(polygon);
    return 0;
}
