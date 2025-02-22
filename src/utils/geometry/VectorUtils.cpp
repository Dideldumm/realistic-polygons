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

CgalTypes::Vector create_random_vector(SeededPointGenerator &point_generator) {
    return {{0, 0}, point_generator.generate_point()};
}
