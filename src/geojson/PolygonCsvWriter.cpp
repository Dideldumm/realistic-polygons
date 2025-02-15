//
// Created by dideldumm on 09.02.25.
//

#include <fstream>

#include "PolygonCsvWriter.h"

#include <iostream>

std::string polygon_to_string(const GeoJsonPolygon &polygon, const unsigned long max_number_of_points) {
    std::string string;
    for (const LatsAndLongs &vertex: polygon.getVertices()) {
        string += std::to_string(vertex.longitude) + ',' + std::to_string(vertex.latitude) + ',';
    }
    const std::string empty_point = "0,0,";
    for (unsigned long i = 0; i < max_number_of_points - polygon.getVertices().size(); ++i) {
        string += empty_point;
    }
    string.pop_back();
    return string;
}

void write_polygons(const std::string &file_path, const std::vector<GeoJsonPolygon> &polygons,
                    const unsigned long max_number_of_points) {
    std::ofstream file(file_path);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << file_path << std::endl;
        return;
    }
    for (const GeoJsonPolygon &polygon: polygons) {
        file << polygon_to_string(polygon, max_number_of_points) << "\n";
    }
    file.close();
    std::ofstream metadata_file(file_path + ".metadata");
    if (!metadata_file.is_open()) {
        std::cerr << "Failed to open metadata file" << std::endl;
        return;
    }
    metadata_file << max_number_of_points << "\n";
    metadata_file << polygons.size() << "\n";
    metadata_file.close();;
}
