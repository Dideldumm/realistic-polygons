//
// Created by dideldumm on 07.02.25.
//
#include <json/json.h>

#include "GeoJsonParser.h"
#include "GeoJsonPolygon.h"
#include "../utils/PolygonMapping.h"

#include "../utils/PolygonCsvWriter.h"


int main(int argc, char **argv) {
    const std::string json_file_path = argv[1];
    const std::string target_file_path = argv[2];
    GeoJsonParser parser(json_file_path);

    const std::vector<GeoJsonPolygon> polygons = parser.parse_all_polygons();
    CsvWriter::write_polygons(target_file_path, map_polygons(polygons), parser.get_max_number_of_vertices());
    return 0;
}
