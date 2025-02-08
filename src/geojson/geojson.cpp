//
// Created by dideldumm on 07.02.25.
//
#include <iostream>
#include <fstream>
#include <optional>

#include <json/json.h>

#include "geojson.h"
#include "GeoJsonPolygon.h"



/// Parse a geojson file to the given root.
/// @param file_path the path to the geojson file
/// @param root a pointer to a json root object where the parsed data should be saved
/// @return @code true@endcode if parsing was successful and @code false@endcode otherwise
bool parse_geojson_file(const std::string &file_path, Json::Value *root) {
    std::ifstream file(file_path, std::ifstream::binary);
    if (!file.is_open()) {
        std::cerr << "Unable to open GeoJSON file.\n";
        return false;
    }

    std::string errs;

    if (Json::CharReaderBuilder reader; !Json::parseFromStream(reader, file, root, &errs)) {
        std::cerr << "Failed to parse GeoJSON:\n" << errs << std::endl;
        return false;
    }
    return true;
}

/// Checks if a json root is a valid geojson root.
/// @param root the root to check
/// @return @code true@endcode when the json-root is a valid geojson-root, @code false@endcode otherwise
bool is_root_valid(const Json::Value &root) {
    // Check if it's a valid GeoJSON FeatureCollection
    if (!root.isMember("type")) {
        std::cerr << "type-member missing in root" << std::endl;
        return false;
    }
    if (root["type"].asString() != "FeatureCollection") {
        std::cerr << "Not a valid GeoJSON FeatureCollection." << std::endl;
        return false;
    }
    if (!root.isMember("features")) {
        std::cerr << "features-member missing in root" << std::endl;
        return false;
    }
    return true;
}

bool is_feature_valid(Json::Value feature) {
    if (!feature.isMember("type") || feature["type"] != "Feature") {
        std::cerr << "Not a valid GEOJSON Feature:\n" << feature << std::endl;
        return false;
    }
    if (!feature.isMember("geometry")) {
        std::cerr << 'Feature has no member "geometry"\n' << feature << std::endl;
        return false;
    }
    const Json::Value geometry = feature["geometry"];
    if (!feature.isMember("type") || !feature.isMember("coordinates")) {
        std::cerr << "geometry object is corrupted:\n" << geometry << std::endl;
        return false;
    }
    return true;
}

std::optional<LatsAndLongs> parse_point(const Json::Value &coordinate) {
    if (!coordinate.isArray() || coordinate.size() < 2) {
        std::cerr << "Not enough values for longitude and latitude: " << coordinate << std::endl;
        return {};
    }
    if (!coordinate[0].isDouble() || !coordinate[1].isDouble()) {
        std::cerr << "Coordinates are not double values: " << coordinate << std::endl;
        return {};
    }
    const double &longitude = coordinate[0].asDouble();
    const double &latitude = coordinate[1].asDouble();
    LatsAndLongs parsed(latitude, longitude);
    return parsed;
}

std::vector<LatsAndLongs> parse_array(const Json::Value &array) {
    if (!array.isArray()) {
        std::cerr << "Could not parse as array:\n" << array << std::endl;
        return {};
    }
    std::vector<LatsAndLongs> points;
    for (const auto &coordinates: array) {
        if (auto maybe_point = parse_point(coordinates); maybe_point.has_value()) {
            points.emplace_back(maybe_point.value());
        }
    }
    return points;
}

std::vector<LatsAndLongs> parse_linestring(const Json::Value &linestring) {
    if (!linestring.isMember("coordinates")) {
        std::cerr << "Could not parse linestring:\n" << linestring << std::endl;
        return {};
    }
    return parse_array(linestring["coordinates"]);
}

std::vector<LatsAndLongs> parse_polygon(const Json::Value &polygon) {
    std::vector<LatsAndLongs> points = parse_linestring(polygon);
    if (points.front() == points.back()) {
        points.pop_back();
    }
    return points;
}

std::vector<std::vector<LatsAndLongs> > parse_multipolygon(const Json::Value &multipolygon) {
    if (!multipolygon.isMember("coordinates")) {
        std::cerr << "Coordinates member missing:\n" << multipolygon << std::endl;
        return {};
    }
    unsigned int failed_counter = 0;
    std::vector<std::vector<LatsAndLongs> > polygons;
    for (const Json::Value &polygon_data: multipolygon["coordinates"]) {
        if (std::vector<LatsAndLongs> parsed_polygon = parse_polygon(polygon_data); parsed_polygon.empty()) {
            failed_counter++;
        } else {
            polygons.emplace_back(parsed_polygon);
        }
    }
    if (failed_counter > 0) {
        std::cerr << "Could not parse " << failed_counter << " out of " << multipolygon["coordinates"].size() <<
                " polygons." << std::endl;
    }
    return polygons;
}

void process_feature(const Json::Value &feature, std::vector<std::vector<LatsAndLongs>> polygons) {
    if (!is_feature_valid(feature)) {
        return;
    }
    switch (Json::Value geometry_value = feature["geometry"]; geometry_value["type"].asString()) {
        case "LineString":
            polygons.emplace_back(parse_linestring(geometry_value));
            break;
        case "Polygon":
            polygons.emplace_back(parse_polygon(geometry_value));
            break;
        case "MultiPolygon":
            auto new_polygons = parse_multipolygon(geometry_value);
            polygons.insert(polygons.end(), new_polygons.begin(), new_polygons.end());
            break;
        default:
            std::cout << "Ignoring geometry of type: " << geometry_value["type"].asString();
            break;
    }
}

double** polygon_to_matrix (const std::vector<LatsAndLongs> &polygon) {

}

int main(int argc, char **argv) {
    const std::string file_path = argv[1];
    Json::Value root;

    parse_geojson_file(file_path, &root);
    if (!is_root_valid(root)) {
        return 1;
    }
    const std::vector<std::vector<LatsAndLongs>> polygons;
    for (const auto feature&: root["features"]) {
        process_feature(feature, polygons);
    }
    for (auto polygon: polygons) {

    }
    return 0;
}
