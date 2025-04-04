//
// Created by dideldumm on 14.12.24.
//

#include "VectorUtils.h"

CgalTypes::Vector map_angle_to_vector(const double &angle) {
    constexpr double hypothenuse = 1;
    //sin(angle) = Gegenkathete / Hypothenuse
    const double y = hypothenuse / sin(angle);
    //cos(angle) = Ankathete / Hypothenuse
    const double x = hypothenuse / cos(angle);
    return {x, y};
}

