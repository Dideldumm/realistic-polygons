//
// Created by dideldumm on 19.09.24.
//

#include <CGAL/draw_polygon_2.h>

#include "TwoOptMoves.h"
#include "utils/PointGenerator/RandomPointGenerator.h"
#include "utils/ToStringUtils.h"

int main(const int argc, char **argv) {
    const int numberOfPoints = argc > 1 ? std::stoi(argv[1]) : 12;

    RandomPointGenerator point_generator(30.0);
    std::vector<Point> points = point_generator.generate_points(numberOfPoints);
    TwoOptMoves two_opt_moves;
    for (Point point: points) {
        two_opt_moves.addPoint(point);
    }
    const CgalTypes::Polygon polygon = two_opt_moves.getPolygon();
    std::cout << "Edges: \n" << containerToString<CgalTypes::Segment>(polygon.edges(), segmentToString, "\n") << std::endl;
    std::cout << "Number of edges: " << polygon.edges().size() << "\n" << std::endl;
    std::cout << "Vertices: \n" << containerToString<Point>(polygon.vertices(), pointToString, "\n") << std::endl;
    std::cout << "Number of vertices: " << polygon.size() << "\n" << std::endl;
    CGAL::draw(polygon);
    return 0;
}
