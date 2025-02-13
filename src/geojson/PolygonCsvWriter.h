//
// Created by dideldumm on 09.02.25.
//

#ifndef POLYGONCSVWRITER_H
#define POLYGONCSVWRITER_H
#include <vector>

#include "GeoJsonPolygon.h"

void write_polygons(const std::string &file_path, const std::vector<GeoJsonPolygon> &polygons);

#endif //POLYGONCSVWRITER_H
