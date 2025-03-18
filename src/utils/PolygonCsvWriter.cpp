//
// Created by dideldumm on 09.02.25.
//

#include <fstream>

#include "PolygonCsvWriter.h"

#include <iostream>

std::string polygon_to_string(const CgalTypes::Polygon &polygon, const unsigned long max_number_of_points) {
    std::string string;
    for (const auto &point: polygon) {
        string += std::to_string(CGAL::to_double(point.x())) + ',' + std::to_string(CGAL::to_double(point.y())) + ',';
    }
    const std::string empty_point = "0,0,";
    for (unsigned long i = 0; i < max_number_of_points - polygon.size(); ++i) {
        string += empty_point;
    }
    string.pop_back();
    return string;
}

void CsvWriter::write_polygons(const std::string &file_path, const std::vector<CgalTypes::Polygon> &polygons,
                               unsigned long max_number_of_points) {
    std::ofstream file(file_path);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << file_path << std::endl;
        return;
    }
    for (const CgalTypes::Polygon &polygon: polygons) {
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
    metadata_file.close();
}
