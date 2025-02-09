//
// Created by dideldumm on 09.02.25.
//

#ifndef GEOJSONPARSER_H
#define GEOJSONPARSER_H
#include <string>

#include <json/json.h>

#include "GeoJsonPolygon.h"

class GeoJsonParser {
private:
    const std::unique_ptr<Json::Value> root;

public:
    explicit GeoJsonParser(const std::string &file_path);

    [[nodiscard]] std::vector<GeoJsonPolygon> parse_all_polygons() const;
};


#endif //GEOJSONPARSER_H
