//
// Created by dideldumm on 17.12.24.
//

#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/convex_hull_2.h>
#include <CGAL/Boolean_set_operations_2.h>
#include <CGAL/draw_polygon_2.h>
#include <CGAL/random_polygon_2.h>

#include "../utils/PointGenerator/SeededPointGenerator.h"
#include "../utils/PointGenerator/RandomPointGenerator.h"
#include "../utils/ToStringUtils.h"
#include "../utils/geometry/PolygonUtils.h"
#include "../utils/geometry/VectorUtils.h"

typedef CGAL::Exact_predicates_exact_constructions_kernel Kernel;
typedef CGAL::Point_2<Kernel> Point;
typedef CGAL::Segment_2<Kernel> Segment;
typedef CGAL::Polygon_2<Kernel> Polygon;
typedef CGAL::Polygon_with_holes_2<Kernel> PolygonWithHoles;

const Point DEFAULT_ORIGIN = {0, 0};

Polygon generate_random_convex_polygon(std::list<Point> vertices) {
    Polygon p;
    CGAL::random_polygon_2(vertices.size(), std::back_inserter(p), vertices.begin());
    ConvexHull hull = create_convex_hull(vertices);
    const Polygon convex_polygon(hull.begin(), hull.end());
    return convex_polygon;
}

Polygon unionOfConvexHulls(const unsigned int max_number_of_points, const unsigned int number_of_polygons, const double
                           max_translation_distance) {
    RandomPointGenerator random_vector_generator(max_translation_distance);
    RandomPointGenerator random_vertex_generator;
    Vector current_vector{0, 0};
    std::vector<Polygon> polygons;
    for (unsigned int i = 0; i < number_of_polygons; ++i) {
        const std::vector<Point> points = random_vertex_generator.generate_points(max_number_of_points);
        std::list<Point> vertices;
        std::ranges::copy(points, std::back_inserter(vertices));

        Polygon next_polygon = generate_random_convex_polygon(vertices);
        Point random_point = random_vector_generator.generate_point();
        const Vector random_vector(random_point.x(), random_point.y());
        current_vector += random_vector;
        Polygon translated_polygon = translate_polygon(next_polygon, current_vector);

        polygons.emplace_back(translated_polygon);
    }
    const Polygon unioned_polygon = join_polygons(polygons);
    return unioned_polygon;
}

int main(int argc, char **argv) {
    const unsigned int number_of_polygons = std::stoi(argv[1]);
    const unsigned int max_number_of_points = std::stoi(argv[2]);
    const double max_translation_distance = std::stod(argv[3]);
    const Polygon result = unionOfConvexHulls(max_number_of_points, number_of_polygons, max_translation_distance);
    std::cout << "---" << std::endl;
    std::cout << polygonToString(result) << std::endl;
    std::cout << "---" << std::endl;
    std::cout << result.vertices().size() << std::endl;
    CGAL::draw(result);
}
