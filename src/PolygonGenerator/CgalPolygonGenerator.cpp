//
// Created by dideldumm on 21.02.25.
//

#include "CgalPolygonGenerator.h"

#include <CGAL/Random.h>
#include <CGAL/point_generators_2.h>
#include <CGAL/random_polygon_2.h>

typedef CGAL::Creator_uniform_2<int, CgalTypes::Point>             Creator;
typedef CGAL::Random_points_in_disc_2<CgalTypes::Point, Creator> Point_generator;

CgalTypes::Polygon generate_simple_polygon(const int &number_of_vertices) {
    CgalTypes::Polygon polygon;

    constexpr int radius = 100000;
    std::list<CgalTypes::Point> random_points;
    CGAL::copy_n_unique(Point_generator(radius), number_of_vertices,
                        std::back_inserter(random_points));
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
