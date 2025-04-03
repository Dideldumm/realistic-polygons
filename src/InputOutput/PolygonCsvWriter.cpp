//
// Created by dideldumm on 09.02.25.
//

#include <fstream>

#include <rapidcsv.h>

#include "PolygonCsvWriter.h"

#include "../../lib/cgal-6.0.1/Kinetic_space_partition/include/CGAL/KSP/utils.h"

int counter = 0;

std::string polygon_to_string(const CgalTypes::Polygon &polygon, unsigned const long max_number_of_points) {
    std::string string;
    for (const auto &point: polygon) {
        string += std::to_string(CGAL::to_double(point.x())) + ',' + std::to_string(CGAL::to_double(point.y())) + ',';
    }
    const std::string empty_point = "0,0,";
    unsigned long end_cond = max_number_of_points - polygon.size();
    if (end_cond > max_number_of_points) {
        end_cond = 0;
    }
    for (unsigned long i = 0; i < end_cond; ++i) {
        string += empty_point;
    }
    string.pop_back();
    return string;
}

std::vector<std::string> build_polygon_csv_row(const CgalTypes::Polygon &polygon,
                                               const unsigned long max_number_of_points) {
    std::vector<std::string> polygon_csv;
    unsigned int i = 0;
    for (const auto &point: polygon) {
        polygon_csv.emplace_back(std::to_string(CGAL::to_double(point.x())));
        polygon_csv.emplace_back(std::to_string(CGAL::to_double(point.y())));
        ++i;
    }

    const unsigned long end_cond = max_number_of_points - polygon.size();
    if (end_cond > max_number_of_points) {
        return polygon_csv;
    }
    for (unsigned long _ = 0; _ < end_cond; ++_) {
        const std::string no_coordinate = "0";
        polygon_csv.emplace_back(no_coordinate);
        polygon_csv.emplace_back(no_coordinate);
    }
    return polygon_csv;
}

void add_polygon_to_csv(const CgalTypes::Polygon &polygon, const unsigned long &max_number_of_points,
                        rapidcsv::Document &doc) {
    const auto csv_row = build_polygon_csv_row(polygon, max_number_of_points);
    doc.InsertRow(counter, csv_row);
    std::cout << "Added: " << counter << std::endl;
    counter++;
}

void CsvWriter::write_polygons(const std::string &file_path, const std::vector<CgalTypes::Polygon> &polygons,
                               const unsigned long max_number_of_points) {
    rapidcsv::Document csv;

    for (auto polygon: polygons) {
        add_polygon_to_csv(polygon, max_number_of_points, csv);
    }

    csv.Save(file_path);
}
