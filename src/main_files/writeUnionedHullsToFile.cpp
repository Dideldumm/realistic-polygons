//
// Created by dideldumm on 20.02.25.
//

#include <random>
#include <string>
#include <vector>

#include <CGAL/IO/Arrangement_2_writer.h>

#include "../PolygonGenerator/UnionOfConvexHullsGenerator.h"
#include "../utils/geometry/CgalTypes.h"
#include "../InputOutput/PolygonCsvWriter.h"
#include "../utils/geometry/PolygonNormalizer.h"


void erase_a_random_point(CgalTypes::Polygon &polygon) {
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distribution(0, polygon.size() - 1);
    const int index = distribution(gen);
    polygon.erase(polygon.begin() + index);
}

void do_work(const int max_points_per_polygon, std::vector<CgalTypes::Polygon> &mapped_polygons, std::mt19937 &gen,
             std::uniform_int_distribution<> &distribution) {
    const int number_of_polygons = distribution(gen);
    CgalTypes::Polygon polygon = union_of_convex_hulls(max_points_per_polygon, number_of_polygons, 1);
    std::cout << "Entering while" << std::endl;
    while (polygon.size() > max_points_per_polygon) {
        // punkte werden random gelöscht, bis die anzahl passt
        erase_a_random_point(polygon);
    }
    std::cout << "Exiting while" << std::endl;

    const CgalTypes::Polygon normal_polygon = normalize_scaling(move_to_origin(polygon));
    mapped_polygons.push_back(normal_polygon);
}

int main(int argc, char *argv[]) {
    const std::string file_path = argv[1];
    const int max_points_per_polygon = std::stoi(argv[2]);
    const int max_polygons_per_union = std::stoi(argv[3]);
    const int number_of_unions = std::stoi(argv[4]);

    std::vector<CgalTypes::Polygon> mapped_polygons;

    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distribution(1, max_polygons_per_union); // define the range

    std::vector<int> iterations;
    for (int i = 0; i < number_of_unions; i++) {
        iterations.push_back(i);
    }
    std::ranges::for_each(iterations, [&](const auto &i) {
        do_work(max_points_per_polygon, mapped_polygons, gen, distribution);
    });
    CsvWriter::write_polygons(file_path, mapped_polygons, max_points_per_polygon);
}
