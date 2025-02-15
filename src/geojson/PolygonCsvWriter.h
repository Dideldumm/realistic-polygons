//
// Created by dideldumm on 09.02.25.
//

#ifndef POLYGONCSVWRITER_H
#define POLYGONCSVWRITER_H
#include <vector>

#include "GeoJsonPolygon.h"

void write_polygons(const std::string &file_path, const std::vector<GeoJsonPolygon> &polygons,
                    const unsigned long max_number_of_points);

#endif //POLYGONCSVWRITER_H
