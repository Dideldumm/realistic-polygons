//
// Created by dideldumm on 22.02.25.
//


#include <CGAL/convex_hull_2.h>

#include "UnionOfConvexHullsGenerator.h"
#include "../utils/geometry/PolygonUtils.h"

typedef CGAL::Creator_uniform_2<CgalTypes::Point, CgalTypes::Vector> VectorCreator;

CgalTypes::Polygon generate_random_convex_polygon(const std::list<CgalTypes::Point> &vertices) {
    std::list<CgalTypes::Point> convex_polygon_vertices;
    CGAL::ch_graham_andrew(vertices.begin(), vertices.end(), std::back_inserter(convex_polygon_vertices));
    // CGAL::convex_hull_2(vertices.begin(), vertices.end(), std::back_inserter(convex_polygon_vertices));
    const CgalTypes::Polygon convex_polygon(convex_polygon_vertices.begin(), convex_polygon_vertices.end());
    return convex_polygon;
}

CgalTypes::Polygon union_of_convex_hulls(const unsigned int max_number_of_points, const unsigned int number_of_polygons,
                                         const double max_translation_distance) {

    CgalTypes::Vector current_vector{0, 0};
    std::vector<CgalTypes::Polygon> polygons;
    for (unsigned int i = 0; i < number_of_polygons; ++i) {
        CgalTypes::PointGenerator random_vector_generator(max_translation_distance);
        CgalTypes::PointGenerator random_vertex_generator(1);

        std::list<CgalTypes::Point> points;
        std::copy_n(std::move(random_vertex_generator), max_number_of_points, std::back_inserter(points));
        CgalTypes::Polygon next_polygon = generate_random_convex_polygon(points);
        const CgalTypes::Point vector_point = *random_vector_generator;
        ++random_vector_generator;

        const CgalTypes::Vector random_vector(vector_point.x(), vector_point.y());
        current_vector += random_vector;
        const CgalTypes::Polygon translated_polygon = translate_polygon(next_polygon, current_vector);
        polygons.emplace_back(translated_polygon);
    }
    const CgalTypes::Polygon unioned_polygon = join_polygons(polygons);
    return unioned_polygon;
}
