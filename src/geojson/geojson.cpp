//
// Created by dideldumm on 07.02.25.
//
#include <json/json.h>

#include "GeoJsonParser.h"
#include "GeoJsonPolygon.h"


int main(int argc, char **argv) {
    const std::string json_file_path = argv[1];
    const std::string target_file_path = argv[2];
    const GeoJsonParser parser(json_file_path);

    std::vector<GeoJsonPolygon> polygons = parser.parse_all_polygons();

    return 0;
}
