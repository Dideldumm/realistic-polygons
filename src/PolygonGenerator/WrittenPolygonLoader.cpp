//
// Created by dideldumm on 26.03.25.
//

#include "WrittenPolygonLoader.h"
#include<rapidcsv.h>

#include <utility>

bool all_zero(const std::vector<float> &values) {
    return std::ranges::all_of(values, [&](const float &value) { return value == 0.0; });
}

bool is_filler_data(const std::vector<float> &coordinates, const unsigned int &i) {
    if (i == coordinates.size() - 2) {
        const float x1 = coordinates[i];
        const float y1 = coordinates[i + 1];
        return all_zero({x1, y1});
    } else if (i < coordinates.size() - 2) {
        const float x1 = coordinates[i];
        const float y1 = coordinates[i + 1];
        const float x2 = coordinates[i + 2];
        const float y2 = coordinates[i + 3];
        return all_zero({x1, y1, x2, y2});
    }
    return false;
}

CgalTypes::Polygon parse_polygon(const std::vector<float> &coordinates) {
    assert(coordinates.size() % 2 == 0);
    std::vector<CgalTypes::Point> vertices;
    for (unsigned int i = 0; i < coordinates.size(); i += 2) {
        if (is_filler_data(coordinates, i)) {
            break;
        }
        float x = coordinates[i];
        float y = coordinates[i + 1];
        CgalTypes::Point point(x, y);
        vertices.push_back(point);
    }
    CgalTypes::Polygon polygon(vertices.begin(), vertices.end());
    return polygon;
}

std::vector<CgalTypes::Polygon> read_lines(const rapidcsv::Document &doc) {
    std::vector<CgalTypes::Polygon> lines;
    for (unsigned int i = 0; i < doc.GetRowCount(); ++i) {
        std::vector<float> polygon_data = doc.GetRow<float>(i);
        const CgalTypes::Polygon polygon = parse_polygon(polygon_data);
        lines.push_back(polygon);
    }
    return lines;
}

void WrittenPolygonLoader::load_file() {
    rapidcsv::Document csvDoc(this->polygonFile, rapidcsv::LabelParams(-1, -1));
    const std::vector<float> probabilities = csvDoc.GetColumn<float>(csvDoc.GetColumnCount() - 1);
    csvDoc.RemoveColumn(csvDoc.GetColumnCount() - 1);
    this->realistic_polygon_probabilities = probabilities;

    const std::vector<CgalTypes::Polygon> polygons = read_lines(csvDoc);
    this->polygons = polygons;
}

WrittenPolygonLoader::WrittenPolygonLoader(std::string polygonFile): polygonFile(std::move(polygonFile)) {
    load_file();
}

std::vector<CgalTypes::Polygon> WrittenPolygonLoader::get_polygons_from_file() {
    return this->polygons;
}

std::vector<float> WrittenPolygonLoader::get_realistic_polygon_probabilities() {
    return this->realistic_polygon_probabilities;
}
