//
// Created by dideldumm on 21.02.25.
//

#include "CgalPolygonGenerator.h"

#include <CGAL/Random.h>
#include <CGAL/random_polygon_2.h>

#include "../utils/PointGenerator/RandomPointGenerator.h"

CgalTypes::Polygon generate_simple_polygon(const int &number_of_vertices) {
    CgalTypes::Polygon polygon;

    constexpr int radius = 1;
    RandomPointGenerator random_point_generator(radius);
    std::vector<CgalTypes::Point> random_points = random_point_generator.generate_points(number_of_vertices);

    CGAL::random_polygon_2(random_points.size(), std::back_inserter(polygon),
                           random_points.begin());
    return polygon;
}

std::vector<CgalTypes::Polygon> generate_polygons(const int &number_of_polygons, const int &max_number_of_vertices) {
    std::vector<CgalTypes::Polygon> polygons;
    polygons.reserve(number_of_polygons);

    for (int i = 0; i < number_of_polygons; ++i) {
        CGAL::Random rand;
        const int size = rand.get_int(4, max_number_of_vertices);
        CgalTypes::Polygon polygon = generate_simple_polygon(size);
        polygons.push_back(polygon);
    }
    return polygons;
}
