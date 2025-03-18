//
// Created by dideldumm on 09.02.25.
//

#ifndef GEOJSONPARSER_H
#define GEOJSONPARSER_H
#include <string>

#include <json/json.h>

#include "../utils/geometry/CgalTypes.h"

class GeoJsonParser {
private:
    const std::unique_ptr<Json::Value> root;
    unsigned long max_number_of_vertices = 0;

public:
    explicit GeoJsonParser(const std::string &file_path);

    [[nodiscard]] std::vector<CgalTypes::Polygon> parse_all_polygons();

    [[nodiscard]] unsigned long get_max_number_of_vertices() const;
};


#endif //GEOJSONPARSER_H
