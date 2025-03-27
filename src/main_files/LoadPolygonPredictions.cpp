//
// Created by dideldumm on 27.03.25.
//

#include <CGAL/draw_polygon_2.h>

#include "../PolygonGenerator/WrittenPolygonLoader.h"

struct PolygonPredictions {
    CgalTypes::Polygon polygon;
    float prediction;

    bool operator<(const PolygonPredictions &other) const {
        return prediction < other.prediction;
    }
};

int main(int argc, char *argv[]) {
    const std::string filePath = argv[1];
    WrittenPolygonLoader polygon_loader(filePath);

    std::vector<PolygonPredictions> polygons_and_predictions;
    std::vector<CgalTypes::Polygon> polygons = polygon_loader.get_polygons_from_file();
    std::vector<float> predictions = polygon_loader.get_realistic_polygon_probabilities();

    assert(polygons.size() == predictions.size());
    for (unsigned int i = 0; i < polygons.size(); ++i) {
        polygons_and_predictions.emplace_back(polygons[i], predictions[i]);
    }
    std::sort(polygons_and_predictions.begin(), polygons_and_predictions.end());
    CGAL::draw(polygons_and_predictions.front().polygon);
    CGAL::draw(polygons_and_predictions.back().polygon);
}
