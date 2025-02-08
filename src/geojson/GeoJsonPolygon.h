//
// Created by dideldumm on 08.02.25.
//

#ifndef GEOJSONPOLYGON_H
#define GEOJSONPOLYGON_H
#include <vector>


struct Point {
    const double x;
    const double y;

    explicit Point(const double &x, const double &y) : x(x), y(y) {
    }

};

struct LatsAndLongs {
    const double latitude;
    const double longitude;

    explicit LatsAndLongs(const double &latitude, const double &longitude) : latitude(latitude), longitude(longitude) {
    }

    bool operator==(const LatsAndLongs &other) const;

    [[nodiscard]] Point to_point() const;

};

class GeoJsonPolygon {
private:


public:
    explicit GeoJsonPolygon(std::vector<LatsAndLongs> vertices);
};



#endif //GEOJSONPOLYGON_H
