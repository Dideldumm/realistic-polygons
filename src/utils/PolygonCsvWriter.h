//
// Created by dideldumm on 09.02.25.
//

#ifndef POLYGONCSVWRITER_H
#define POLYGONCSVWRITER_H
#include <vector>

namespace CsvWriter {
    struct Point {
        double x;
        double y;
    };

    typedef std::vector<Point> Polygon;

    void write_polygons(const std::string &file_path, const std::vector<Polygon> &polygons,
                        unsigned long max_number_of_points);
}
#endif //POLYGONCSVWRITER_H
