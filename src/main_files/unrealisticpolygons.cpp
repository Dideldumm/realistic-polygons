//
// Created by dideldumm on 13.02.25.
//

#include <string>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Polygon_2.h>

#include "../utils/PolygonCsvWriter.h"
#include "../PolygonGenerator/CgalPolygonGenerator.h"


int main(int argc, char *argv[]) {
    const std::string file_path = argv[1];
    const int max_number_of_points = std::stoi(argv[2]);
    // Each point corresponds to 2 features (x and y coordinate of that point)
    const int number_of_polygons = std::stoi(argv[3]);

    std::vector<CgalTypes::Polygon> mapped_polygons;
    for (int i = 0; i < number_of_polygons; i++) {
        const CgalTypes::Polygon polygon = generate_simple_polygon(max_number_of_points);
        std::cout << "Polygon: " << i << std::endl;
        mapped_polygons.push_back(polygon);
    }

    CsvWriter::write_polygons(file_path, mapped_polygons, max_number_of_points);
}
