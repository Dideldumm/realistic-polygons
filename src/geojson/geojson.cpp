//
// Created by dideldumm on 07.02.25.
//
#include <iostream>
#include <fstream>
#include <json/json.h>

#include "geojson.h"

#include <optional>

struct Coordinates {
    const double latitude;
    const double longitude;

    Coordinates(const double &latitude, const double &longitude) : latitude(latitude), longitude(longitude) {
    }

    bool operator==(const Coordinates &other) const {
        return latitude == other.latitude && longitude == other.longitude;
    }
};

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

std::optional<Coordinates> parse_coordinates(const Json::Value &coordinate) {
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
    Coordinates parsed(latitude, longitude);
    return parsed;
}

std::vector<Coordinates> parse_array(const Json::Value &array) {
    if (!array.isArray()) {
        std::cerr << "Could not parse as array:\n" << array << std::endl;
        return {};
    }
    std::vector<Coordinates> points;
    for (const auto &coordinates: array) {
        if (auto maybe_point = parse_coordinates(coordinates); maybe_point.has_value()) {
            points.emplace_back(maybe_point.value());
        }
    }
    return points;
}

std::vector<Coordinates> parse_linestring(const Json::Value &linestring) {
    if (!linestring.isMember("coordinates")) {
        std::cerr << "Could not parse linestring:\n" << linestring << std::endl;
        return {};
    }
    return parse_array(linestring["coordinates"]);
}

std::vector<Coordinates> parse_polygon(const Json::Value &polygon) {
    std::vector<Coordinates> points = parse_linestring(polygon);
    if (points.front() == points.back()) {
        points.pop_back();
    }
    return points;
}

void process_feature(const Json::Value &feature) {
}

int main(int argc, char **argv) {
    const std::string file_path = argv[1];
    Json::Value root;

    parse_geojson_file(file_path, &root);
    if (!is_root_valid(root)) {
        return 1;
    }

    for (const auto feature&: root["features"]) {
        process_feature(feature);
    }
    return 0;
}
