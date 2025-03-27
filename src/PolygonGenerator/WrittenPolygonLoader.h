//
// Created by dideldumm on 26.03.25.
//

#ifndef WRITTENPOLYGONLOADER_H
#define WRITTENPOLYGONLOADER_H

#include <string>

#include "../utils/geometry/CgalTypes.h"

class WrittenPolygonLoader {
private:
    const std::string polygonFile;

    std::vector<CgalTypes::Polygon> polygons;
    std::vector<float> realistic_polygon_probabilities;

    void load_file();

public:
    explicit WrittenPolygonLoader(std::string polygonFile);

    std::vector<CgalTypes::Polygon> get_polygons_from_file();

    std::vector<float> get_realistic_polygon_probabilities();
};


#endif //WRITTENPOLYGONLOADER_H
