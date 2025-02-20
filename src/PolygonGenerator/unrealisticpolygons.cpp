//
// Created by dideldumm on 13.02.25.
//

#include <string>
#include <CGAL/Polygon_2.h>
#include <CGAL/Random.h>
#include <CGAL/random_polygon_2.h>

#include "../geojson/GeoJsonPolygon.h"
#include "../utils/PolygonCsvWriter.h"
#include "../utils/PointGenerator/RandomPointGenerator.h"

typedef CGAL::Polygon_2<Kernel> Polygon;
typedef Kernel::Point_2 Point;
typedef CGAL::Creator_uniform_2<int, Point> Creator;

LatsAndLongs map_cgal_point(const Point &p) {
    return {CGAL::to_double(p.x()), CGAL::to_double(p.y())};
}

GeoJsonPolygon map_cgal_polygon(const Polygon &polygon) {
    std::vector<LatsAndLongs> lats_and_longs;
    lats_and_longs.reserve(polygon.size());
    std::ranges::transform(polygon.vertices(), std::back_inserter(lats_and_longs), map_cgal_point);
    return GeoJsonPolygon(lats_and_longs);
}

Polygon generate_simple_polygon(const int &number_of_vertices) {
    Polygon polygon;
    CGAL::Random rand;

    const int size = rand.get_int(4, number_of_vertices);
    constexpr int radius = 1; // TODO

    RandomPointGenerator random_point_generator(radius);
    std::vector<Point> random_points = random_point_generator.generate_points(size);

    CGAL::random_polygon_2(random_points.size(), std::back_inserter(polygon),
                           random_points.begin());
    return polygon;
}

int main(int argc, char *argv[]) {
    const std::string file_path = argv[1];
    const int max_number_of_points = std::stoi(argv[2]);
    // Each point corresponds to 2 features (x and y coordinate of that point)
    const int number_of_polygons = std::stoi(argv[3]);

    std::vector<GeoJsonPolygon> mapped_polygons;
    for (int i = 0; i < number_of_polygons; i++) {
        const Polygon polygon = generate_simple_polygon(max_number_of_points);
        mapped_polygons.push_back(map_cgal_polygon(polygon));
    }

    write_polygons(file_path, mapped_polygons, max_number_of_points);
}
