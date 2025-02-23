//
// Created by dideldumm on 07.02.25.
//
#include <json/json.h>

#include "GeoJsonParser.h"
#include "GeoJsonPolygon.h"
#include "../utils/PolygonMapping.h"

#include "../utils/PolygonCsvWriter.h"
#include "GeojsonPolygonTransformer.h"


int main(int argc, char **argv) {
    const std::string json_file_path = argv[1];
    const std::string target_file_path = argv[2];
    GeoJsonParser parser(json_file_path);

    const std::vector<GeoJsonPolygon> polygons = parser.parse_all_polygons();
    std::vector<GeoJsonPolygon> normalized_polygons;
    for (const GeoJsonPolygon &polygon: polygons) {
        GeoJsonPolygon moved_polygon = move_to_origin(polygon);
        GeoJsonPolygon normalized_polygon = normalize_scaling(moved_polygon);
        normalized_polygons.push_back(normalized_polygon);
    }
    CsvWriter::write_polygons(target_file_path, map_polygons(polygons), parser.get_max_number_of_vertices());
    return 0;
}
