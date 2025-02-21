//
// Created by dideldumm on 13.02.25.
//

#include <string>
#include <CGAL/Polygon_2.h>
#include <CGAL/Random.h>
#include <CGAL/random_polygon_2.h>

#include "../utils/PolygonCsvWriter.h"
#include "../utils/PointGenerator/RandomPointGenerator.h"


typedef CGAL::Polygon_2<Kernel> CGAL_Polygon;
typedef Kernel::Point_2 CGAL_Point;




int main(int argc, char *argv[]) {
    const std::string file_path = argv[1];
    const int max_number_of_points = std::stoi(argv[2]);
    // Each point corresponds to 2 features (x and y coordinate of that point)
    const int number_of_polygons = std::stoi(argv[3]);

    std::vector<CsvWriter::Polygon> mapped_polygons;
    for (int i = 0; i < number_of_polygons; i++) {
        const CGAL_Polygon polygon = generate_simple_polygon(max_number_of_points);
        mapped_polygons.push_back(map_cgal_polygon(polygon));
    }

    write_polygons(file_path, mapped_polygons, max_number_of_points);
}
