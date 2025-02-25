//
// Created by dideldumm on 20.02.25.
//

#include <string>
#include <vector>

#include "../PolygonGenerator/UnionOfConvexHullsGenerator.h"
#include "../utils/PolygonMapping.h"
#include "../utils/geometry/CgalTypes.h"
#include "../utils/PolygonCsvWriter.h"


int main(int argc, char *argv[]) {
    const std::string file_path = argv[1];
    const int max_number_of_points = std::stoi(argv[2]);
    const int number_of_polygons = std::stoi(argv[3]);

    std::vector<CsvWriter::Polygon> mapped_polygons;
    for (int i = 0; i < number_of_polygons; i++) {
        const CgalTypes::Polygon polygon = unionOfConvexHulls(max_number_of_points, number_of_polygons, 1);
        mapped_polygons.push_back(map_polygon(polygon));
    }

    write_polygons(file_path, mapped_polygons, max_number_of_points);
}
