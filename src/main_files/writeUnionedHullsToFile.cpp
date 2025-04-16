//
// Created by dideldumm on 20.02.25.
//

#include <execution>
#include <random>
#include <string>
#include <vector>

#include <CGAL/IO/Arrangement_2_writer.h>
#include <pstl/glue_execution_defs.h>

#include "../PolygonGenerator/UnionOfConvexHullsGenerator.h"
#include "../utils/geometry/CgalTypes.h"
#include "../InputOutput/PolygonCsvWriter.h"


void erase_a_random_point(CgalTypes::Polygon &polygon) {
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distribution(0, static_cast<int>(polygon.size()) - 1);
    const int index = distribution(gen);
    polygon.erase(polygon.begin() + index);
}

// void do_work(const unsigned int max_points_per_polygon, std::vector<CgalTypes::Polygon> &mapped_polygons, std::mt19937 &gen,
//              std::uniform_int_distribution<> &distribution) {
//     const int number_of_polygons = distribution(gen);
//     CgalTypes::Polygon polygon = union_of_convex_hulls(max_points_per_polygon, number_of_polygons, 1);
//     while (polygon.size() > max_points_per_polygon) {
//         // delete points randomly until the polygons size is ok
//         erase_a_random_point(polygon);
//     }
//
//     const CgalTypes::Polygon normal_polygon = normalize_scaling(move_to_origin(polygon));
//     mapped_polygons.push_back(normal_polygon);
// }

CgalTypes::Polygon generate_simple_polygon(const unsigned int &max_points_per_polygon, const int &number_of_hulls) {
    CgalTypes::Polygon polygon = union_of_convex_hulls(max_points_per_polygon, number_of_hulls, 1);
    while (polygon.size() > max_points_per_polygon) {
        erase_a_random_point(polygon);
    }
    return polygon;
}

int main(const int argc, char *argv[]) {
    assert(argc > 4);
    const std::string file_path = argv[1];
    const unsigned int max_points_per_polygon = std::stoi(argv[2]);
    const int max_polygons_per_union = std::stoi(argv[3]);
    const int number_of_unions = std::stoi(argv[4]);

    std::vector<CgalTypes::Polygon> mapped_polygons(number_of_unions);

    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distribution(1, max_polygons_per_union); // define the range

    std::vector<int> random_sizes(number_of_unions);
    for (int i = 0; i < number_of_unions; i++) {
        random_sizes[i] = distribution(gen);
    }
    std::atomic iteration(0);
    std::generate(std::execution::par, mapped_polygons.begin(), mapped_polygons.end(), [&]() {
        const int this_iteration = iteration.fetch_add(1);
        const int size = random_sizes[this_iteration];
        return generate_simple_polygon(max_points_per_polygon, size);
    });
    // std::ranges::for_each(iterations, [&](const auto &_) {
    //     do_work(max_points_per_polygon, mapped_polygons, gen, distribution);
    // });
    CsvWriter::write_polygons(file_path, mapped_polygons, max_points_per_polygon);
}
