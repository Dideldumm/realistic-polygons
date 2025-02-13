//
// Created by dideldumm on 08.02.25.
//

#include "GeoJsonPolygon.h"

#include <format>

LatsAndLongs::LatsAndLongs(const double &latitude, const double &longitude): latitude(latitude), longitude(longitude) {
}

LatsAndLongs::LatsAndLongs(const LatsAndLongs &other) = default;


bool LatsAndLongs::operator==(const LatsAndLongs &other) const {
    return latitude == other.latitude && longitude == other.longitude;
}

std::string LatsAndLongs::to_string() const {
    return std::format("{}|{}", longitude, latitude);
}

GeoJsonPolygon::GeoJsonPolygon(const std::vector<LatsAndLongs> &vertices) : vertices(vertices) {
}

const std::vector<LatsAndLongs> &GeoJsonPolygon::getVertices() const {
    return vertices;
}
