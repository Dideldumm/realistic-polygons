//
// Created by dideldumm on 22.02.25.
//


#include <CGAL/convex_hull_2.h>

#include "UnionOfConvexHullsGenerator.h"
#include "../utils/PointGenerator/RandomPointGenerator.h"
#include "../utils/geometry/PolygonUtils.h"

CgalTypes::Polygon generate_random_convex_polygon(const std::list<CgalTypes::Point> &vertices) {
    std::vector<CgalTypes::Point> new_hull;
    CGAL::convex_hull_2(vertices.begin(), vertices.end(), std::back_inserter(new_hull));
    const CgalTypes::Polygon convex_polygon(new_hull.begin(), new_hull.end());
    return convex_polygon;
}

CgalTypes::Polygon drawUnionOfConvexHulls(const unsigned int max_number_of_points, const unsigned int number_of_polygons, const double
                                      max_translation_distance) {
    RandomPointGenerator random_vector_generator(max_translation_distance);
    RandomPointGenerator random_vertex_generator;

    CgalTypes::Vector current_vector{0, 0};
    std::vector<CgalTypes::Polygon> polygons;
    for (unsigned int i = 0; i < number_of_polygons; ++i) {
        const std::vector<CgalTypes::Point> points = random_vertex_generator.generate_points(max_number_of_points);
        std::list<CgalTypes::Point> vertices;
        std::ranges::copy(points, std::back_inserter(vertices));

        CgalTypes::Polygon next_polygon = generate_random_convex_polygon(vertices);
        CgalTypes::Point random_point = random_vector_generator.generate_point();
        const CGAL::Vector_2<CgalTypes::Kernel> random_vector(random_point.x(), random_point.y());
        current_vector += random_vector;
        CgalTypes::Polygon translated_polygon = translate_polygon(next_polygon, current_vector);

        polygons.emplace_back(translated_polygon);
    }
    const CgalTypes::Polygon unioned_polygon = join_polygons(polygons);
    return unioned_polygon;
}
