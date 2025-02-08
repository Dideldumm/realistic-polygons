//
// Created by dideldumm on 08.02.25.
//

#include "GeoJsonPolygon.h"

bool LatsAndLongs::operator==(const LatsAndLongs &other) const {
    return latitude == other.latitude && longitude == other.longitude;
}

Point LatsAndLongs::to_point() const {
    //TODO implement
}
