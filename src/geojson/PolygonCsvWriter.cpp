//
// Created by dideldumm on 09.02.25.
//

#include <fstream>

#include "PolygonCsvWriter.h"

#include <iostream>

static unsigned int max_number_of_features = 0;

std::string polygon_to_string(const GeoJsonPolygon &polygon) {
    std::string string;
    unsigned int number_of_features = 0;
    for (const LatsAndLongs& vertex: polygon.getVertices()) {
        string += std::to_string(vertex.longitude) + ',' + std::to_string(vertex.latitude) + ',';
        number_of_features += 2;
    }
    if (number_of_features > max_number_of_features) {
        max_number_of_features = number_of_features;
    }
    string.pop_back();
    return string;
}

void write_polygons(const std::string &file_path, const std::vector<GeoJsonPolygon> &polygons) {
    std::ofstream file(file_path);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << file_path << std::endl;
        return;
    }
    for (const GeoJsonPolygon &polygon: polygons) {
        file << polygon_to_string(polygon) << "\n";
    }
    file.close();
    std::ofstream metadata_file(file_path + ".metadata");
    if (!metadata_file.is_open()) {
        std::cerr << "Failed to open metadata file" << std::endl;
        return;
    }
    metadata_file << max_number_of_features << "\n";
    metadata_file.close();
}
