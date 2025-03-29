//
// Created by dideldumm on 09.02.25.
//

#ifndef POLYGONCSVWRITER_H
#define POLYGONCSVWRITER_H
#include <vector>

#include "../utils/geometry/CgalTypes.h"

namespace CsvWriter {
    void write_polygons(const std::string &file_path, const std::vector<CgalTypes::Polygon> &polygons,
                        const unsigned long max_number_of_points);
}
#endif //POLYGONCSVWRITER_H
