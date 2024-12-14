//
// Created by dideldumm on 19.10.24.
//


#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/convex_hull_2.h>
#include <CGAL/random_polygon_2.h>
#include <CGAL/Boolean_set_operations_2.h>
#include <CGAL/draw_polygon_2.h>

#include "utils/PointGenerator/SeededPointGenerator.h"
#include "utils/PointGenerator/RandomPointGenerator.h"
#include "utils/ToStringUtils.h"
#include "utils/geometry/PolygonUtils.h"
#include "utils/geometry/VectorUtils.h"

typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef CGAL::Point_2<Kernel> Point;
typedef CGAL::Segment_2<Kernel> Segment;
typedef CGAL::Polygon_2<Kernel> Polygon;
typedef CGAL::Polygon_with_holes_2<Kernel> PolygonWithHoles;

constexpr unsigned int number_of_polygons = 15;
constexpr unsigned int max_number_of_points = 100;

Polygon generate_random_convex_polygon(const Point &origin) {
    RandomPointGenerator generator(max_number_of_points, origin);
    std::vector<Point> vector = generator.generate_points(max_number_of_points);
    std::list<Point> points;
    std::ranges::copy(vector, std::back_inserter(points));
    Polygon p;
    CGAL::random_polygon_2(points.size(), std::back_inserter(p), points.begin());
    ConvexHull hull = create_convex_hull(points);
    const Vector translation_vector = create_random_vector(generator);
    const Polygon generated_polygon(hull.begin(), hull.end());
    const Polygon translated_polygon = translate_polygon(generated_polygon, translation_vector);
    return translated_polygon;
}

int main() {
    constexpr Point origin = {0, 0};
    std::vector<Polygon> polygons;
    for (unsigned int i = 0; i < number_of_polygons; ++i) {
        Polygon next_polygon = generate_random_convex_polygon(origin);
        polygons.emplace_back(next_polygon);
    }
    const Polygon result = join_polygons(polygons);
    CGAL::draw(result);
}
