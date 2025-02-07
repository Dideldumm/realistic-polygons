//
// Created by dideldumm on 07.02.25.
//
#include <iostream>
#include <fstream>
#include <json/json.h>

#include "geojson.h"

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
        std::cerr << "Not a valid GeoJSON FeatureCollection.\n";
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

std::vector<std::pair<double, double>> get_coordinates(Json::Value feature) {

}



void process_feature(const Json::Value& feature) {

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
