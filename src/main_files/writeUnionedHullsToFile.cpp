//
// Created by dideldumm on 20.02.25.
//

#include <random>
#include <string>
#include <vector>

#include "../PolygonGenerator/UnionOfConvexHullsGenerator.h"
#include "../utils/geometry/CgalTypes.h"
#include "../utils/PolygonCsvWriter.h"
#include "../utils/geometry/PolygonNormalizer.h"


int main(int argc, char *argv[]) {
    const std::string file_path = argv[1];
    const int max_points_per_polygon = std::stoi(argv[2]);
    const int max_polygons_per_union = std::stoi(argv[3]);
    const int number_of_unions = std::stoi(argv[4]);

    std::vector<CgalTypes::Polygon> mapped_polygons;

    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(1, max_polygons_per_union); // define the range
    for (int i = 0; i < number_of_unions; i++) {
        // TODO max_number_of_points is the maximum number of points for a single polygon not for the union
        // momentan nur temporäre Lösung: alle Punkte, die zu viel sind löschen
        const int number = distr(gen);
        CgalTypes::Polygon polygon = union_of_convex_hulls(max_points_per_polygon, number, 1);
        if (polygon.size() > max_points_per_polygon) {
            auto it = polygon.vertices_begin();
            it += max_points_per_polygon;
            polygon.erase(it, polygon.vertices_end());
        }
        CgalTypes::Polygon normal_polygon = normalize_scaling(move_to_origin(polygon));
        mapped_polygons.push_back(normal_polygon);
    }
    CsvWriter::write_polygons(file_path, mapped_polygons, max_points_per_polygon);
}
