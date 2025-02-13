//
// Created by dideldumm on 08.02.25.
//

#ifndef GEOJSONPOLYGON_H
#define GEOJSONPOLYGON_H
#include <string>
#include <vector>

struct LatsAndLongs {
    double latitude;
    double longitude;

    LatsAndLongs(const double &latitude, const double &longitude);

    LatsAndLongs(const LatsAndLongs &other);

    bool operator==(const LatsAndLongs &other) const;

    [[nodiscard]] std::string to_string() const;
};

class GeoJsonPolygon {
private:
    std::vector<LatsAndLongs> vertices;

public:
    explicit GeoJsonPolygon(const std::vector<LatsAndLongs> &vertices);

    [[nodiscard]] const std::vector<LatsAndLongs> &getVertices() const;
};

#endif //GEOJSONPOLYGON_H
