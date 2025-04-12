//
// Created by dideldumm on 17.12.24.
//

#include <random>
#include <execution>

#include <CGAL/Polygon_2.h>

#include "../PolygonGenerator/UnionOfConvexHullsGenerator.h"
#include "../utils/geometry/PolygonNormalizer.h"
#include "../InputOutput/PolygonImageSaver.h"

int random_number_in_range(const int lower_bound, const int &upper_bound) {
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distribution(lower_bound, upper_bound); // define the range
    return distribution(gen);
}

void erase_a_random_point(CgalTypes::Polygon &polygon) {
    const int index = random_number_in_range(0, static_cast<int>(polygon.size() - 1));
    polygon.erase(polygon.begin() + index);
}

CgalTypes::Polygon generate_a_union(const unsigned int max_points_per_polygon, const int max_polygons_per_union) {
    const int number_of_polygons = random_number_in_range(1, max_polygons_per_union);
    const CgalTypes::Polygon polygon = union_of_convex_hulls(max_points_per_polygon, number_of_polygons, 1);

    const CgalTypes::Polygon normal_polygon = normalize_scaling(move_to_origin(polygon));
    return normal_polygon;
}

void save_polygon_images(const std::string &image_directory, const std::vector<CgalTypes::Polygon> &polygons,
                         const std::string &class_name) {
    for (unsigned int i = 0; i < polygons.size(); ++i) {
        const CgalTypes::Polygon &polygon = polygons[i];
        const QImage image = polygon_to_image(polygon);
        const std::string file_path = image_directory + class_name + "_image_" + std::to_string(i) + ".jpg";
        save_image(image, file_path);
    }
}

int main(const int argc, char **argv) {
    assert(argc > 3);
    const std::string file_path = argv[1];
    const unsigned int max_points_per_polygon = std::stoi(argv[2]);
    const int max_polygons_per_union = std::stoi(argv[3]);
    const int number_of_unions = std::stoi(argv[4]);

    std::vector<CgalTypes::Polygon> mapped_polygons(number_of_unions);
    int i = 0;
    std::generate(std::execution::par, mapped_polygons.begin(), mapped_polygons.end(),
                  [&]() {
                      std::cout << "start generating polygon " << i++ << std::endl;
                      return generate_a_union(max_points_per_polygon, max_polygons_per_union);
                  }
    );
    // for (int i = 0; i < number_of_unions; ++i) {
    //     const CgalTypes::Polygon polygon = generate_a_union(max_points_per_polygon, max_polygons_per_union);
    //     mapped_polygons[i] = polygon;
    //     std::cout << "polygon " << i << " generated" << std::endl;
    // }

    save_polygon_images("data/generated/", mapped_polygons, "union");
}
