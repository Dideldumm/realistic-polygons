//
// Created by dideldumm on 13.02.25.
//

#include <string>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Polygon_2.h>
#include <execution>

#include "../InputOutput/PolygonCsvWriter.h"
#include "../PolygonGenerator/CgalPolygonGenerator.h"

int main(int argc, char *argv[]) {
    const std::string file_path = argv[1];
    const int max_number_of_points = std::stoi(argv[2]);
    // Each point corresponds to 2 features (x and y coordinate of that point)
    const int number_of_polygons = std::stoi(argv[3]);

    std::vector<CgalTypes::Polygon> polygons(number_of_polygons);
    std::atomic<int> i = 0;
    std::generate(std::execution::par, polygons.begin(), polygons.end(),
                  [&]() {
                      const int current = i.fetch_add(1, std::memory_order_relaxed);
                      std::cout << "begin: " << current << std::endl;
                      auto polygon = generate_simple_polygon(max_number_of_points);
                      std::cout << "finished: " << current << std::endl;
                      return polygon;
                  });

    std::cout << "finished generating" << std::endl;
    CsvWriter::write_polygons(file_path, polygons, max_number_of_points);
}
