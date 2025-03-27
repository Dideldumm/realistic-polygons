//
// Created by dideldumm on 07.02.25.
//

#include "../PolygonGenerator/GeoJsonParser.h"

#include "../utils/PolygonCsvWriter.h"
#include "../utils/geometry/PolygonNormalizer.h"


int main(int argc, char **argv) {
    const std::string json_file_path = argv[1];
    const std::string target_file_path = argv[2];
    GeoJsonParser parser(json_file_path);

    const std::vector<CgalTypes::Polygon> polygons = parser.parse_all_polygons();
    std::vector<CgalTypes::Polygon> normalized_polygons;
    for (const CgalTypes::Polygon &polygon: polygons) {
        CgalTypes::Polygon moved_polygon = move_to_origin(polygon);
        CgalTypes::Polygon normalized_polygon = normalize_scaling(moved_polygon);
        normalized_polygons.push_back(normalized_polygon);
    }
    CsvWriter::write_polygons(target_file_path, polygons, parser.get_max_number_of_vertices());
    return 0;
}
