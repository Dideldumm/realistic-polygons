//
// Created by dideldumm on 13.02.25.
//

#include <string>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/Random.h>
#include <CGAL/random_polygon_2.h>

#include "../geojson/GeoJsonPolygon.h"
#include "../geojson/PolygonCsvWriter.h"

typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef CGAL::Polygon_2<Kernel> Polygon;
typedef Kernel::Point_2 Point;
typedef CGAL::Creator_uniform_2<int, Point> Creator;
typedef CGAL::Random<Point, Creator> Point_generator;

LatsAndLongs map_cgal_point(const Point &p) {
    return {p.x(), p.y()};
}

GeoJsonPolygon map_cgal_polygon(const Polygon &polygon) {
    std::vector<LatsAndLongs> lats_and_longs;
    std::ranges::transform(polygon.vertices(), lats_and_longs.begin(), map_cgal_point);
    return GeoJsonPolygon(lats_and_longs);
}

Polygon generate_simple_polygon(const int &number_of_vertices) {
    Polygon polygon;
    std::list<Point> point_set;
    CGAL::Random rand;

    const int size = rand.get_int(4, number_of_vertices);
    constexpr int radius = 1; // TODO

    // copy size points from the generator, eliminating duplicates, so the
    // polygon will have <= size vertices
    CGAL::copy_n_unique(Point_generator(radius), size,
                        std::back_inserter(point_set));

    const std::ostream_iterator<Point> out(std::cout, " ");
    std::cout << "From the following " << point_set.size() << " points " << std::endl;
    std::ranges::copy(point_set, out);
    std::cout << std::endl;

    CGAL::random_polygon_2(point_set.size(), std::back_inserter(polygon),
                           point_set.begin());
    std::cout << "The following simple polygon was made: " << std::endl;
    std::cout << polygon << std::endl;
    return polygon;
}

int main(int argc, char *argv[]) {
    const std::string file_path = argv[1];
    const int number_of_polygons = std::stoi(argv[2]);
    const int max_number_of_points = std::stoi(argv[3]);

    std::vector<GeoJsonPolygon> mapped_polygons;
    for (int i = 0; i < number_of_polygons; i++) {
        const Polygon polygon = generate_simple_polygon(max_number_of_points);
        mapped_polygons.push_back(map_cgal_polygon(polygon));
    }

    write_polygons(file_path, mapped_polygons);
}
