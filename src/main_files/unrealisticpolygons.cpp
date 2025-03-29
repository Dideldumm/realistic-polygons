//
// Created by dideldumm on 13.02.25.
//

#include <string>
#include <execution>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Polygon_2.h>

#include "../InputOutput/PolygonCsvWriter.h"
#include "../PolygonGenerator/CgalPolygonGenerator.h"


void generate_and_addPolygon(std::vector<CgalTypes::Polygon> &vector, const int &max_number_of_points,
                             const int &current_iteration) {
    const CgalTypes::Polygon polygon = generate_simple_polygon(max_number_of_points);
    vector.push_back(polygon);
    std::cout << "Polygon: " << current_iteration << std::endl;
}

int main(int argc, char *argv[]) {
    const std::string file_path = argv[1];
    const int max_number_of_points = std::stoi(argv[2]);
    // Each point corresponds to 2 features (x and y coordinate of that point)
    const int number_of_polygons = std::stoi(argv[3]);

    std::vector<CgalTypes::Polygon> mapped_polygons;
    std::vector<int> indices(number_of_polygons);

    for (int i = 0; i < number_of_polygons; i++) {
        indices[i] = i;
    }

    std::for_each(std::execution::par_unseq, indices.begin(), indices.end(), [&](const int &i) {
        generate_and_addPolygon(mapped_polygons, max_number_of_points, i);
    });

    CsvWriter::write_polygons(file_path, mapped_polygons, max_number_of_points);
}
