//
// Created by dideldumm on 09.02.25.
//

#include "GeoJsonParser.h"

#include <fstream>
#include <iostream>

std::unique_ptr<Json::Value> read_file(const std::string &file_path) {
    std::ifstream file(file_path);
    if (!file.is_open()) {
        std::cerr << "Unable to open GeoJSON file." << std::endl;
        return nullptr;
    }

    std::string errs;
    auto root = std::make_unique<Json::Value>();

    if (Json::CharReaderBuilder reader; !Json::parseFromStream(reader, file, root.get(), &errs)) {
        std::cerr << "Failed to parse GeoJSON:\n" << errs << std::endl;
        return nullptr;
    }
    return root;
}

GeoJsonParser::GeoJsonParser(const std::string &file_path): root(read_file(file_path)) {
}

LatsAndLongs parse_point(const Json::Value &coordinate) {
    const double &longitude = coordinate[0].asDouble();
    const double &latitude = coordinate[1].asDouble();
    return {latitude, longitude};
}

std::vector<LatsAndLongs> parse_array(const Json::Value &array) {
    std::vector<LatsAndLongs> points;
    points.reserve(array.size());
    for (const auto &coordinates: array) {
        points.emplace_back(parse_point(coordinates));
    }
    return points;
}

GeoJsonPolygon parse_linestring(const Json::Value &coordinates) {
    return GeoJsonPolygon(parse_array(coordinates));
}

GeoJsonPolygon parse_polygon(const Json::Value &coordinates) {
    std::vector<LatsAndLongs> points = parse_array(coordinates);
    points.pop_back();
    return GeoJsonPolygon(points);
}

std::vector<GeoJsonPolygon> parse_multipolygon(const Json::Value &multipolygon) {
    std::vector<GeoJsonPolygon> polygons;
    for (const Json::Value &polygon_data: multipolygon) {
        polygons.emplace_back(parse_polygon(polygon_data));
    }
    return polygons;
}

std::vector<GeoJsonPolygon> GeoJsonParser::parse_all_polygons() {
    const Json::Value &root = *(this->root);
    std::vector<GeoJsonPolygon> polygons;
    polygons.reserve(root["features"].size());
    for (Json::Value feature: root["features"]) {
        const Json::Value &geometry_data = feature["geometry"];
        const Json::Value &coordinates = geometry_data["coordinates"];
        const std::string geometry_type = geometry_data["type"].asString();
        if (geometry_type == "LineString") {
            GeoJsonPolygon polygon = parse_linestring(coordinates);
            polygons.emplace_back(polygon);
            if (polygon.getVertices().size() > max_number_of_vertices) {
                max_number_of_vertices = polygon.getVertices().size();
            }
        } else if (geometry_type == "Polygon") {
            GeoJsonPolygon polygon = parse_polygon(coordinates);
            polygons.emplace_back(polygon);
            if (polygon.getVertices().size() > max_number_of_vertices) {
                max_number_of_vertices = polygon.getVertices().size();
            }
        } else if (geometry_type == "MultiPolygon") {
            // TODO fix
            // std::vector<GeoJsonPolygon> multipolygon = parse_multipolygon(coordinates);
            // polygons.insert(polygons.end(), multipolygon.begin(), multipolygon.end());
        } else {
            //TODO log the skipped lines?
        }
    }
    return polygons;
}

unsigned long GeoJsonParser::get_max_number_of_vertices() const {
    return max_number_of_vertices;
}
