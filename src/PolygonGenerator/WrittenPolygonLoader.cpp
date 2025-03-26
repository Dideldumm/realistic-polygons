//
// Created by dideldumm on 26.03.25.
//

#include "WrittenPolygonLoader.h"
#include<rapidcsv.h>

CgalTypes::Polygon parse_polygon(const std::vector<float> &coordinates) {
    assert(coordinates.size() % 2 == 0);
    std::vector<CgalTypes::Point> vertices;
    for (int i = 0; i < coordinates.size(); i += 2) {
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
    for (int i = 0; i < doc.GetRowCount(); ++i) {
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

WrittenPolygonLoader::WrittenPolygonLoader(const std::string &polygonFile): polygonFile(polygonFile) {
    load_file();
}

std::vector<CgalTypes::Polygon> WrittenPolygonLoader::get_polygons_from_file() {
    return this->polygons;
}

std::vector<float> WrittenPolygonLoader::get_realistic_polygon_probabilities() {
    return this->realistic_polygon_probabilities;
}
