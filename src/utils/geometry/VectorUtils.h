//
// Created by dideldumm on 14.12.24.
//

#ifndef VECTORUTILS_H
#define VECTORUTILS_H

#include "../geometry/CgalTypes.h"


/**
 * Transforms the given angle to a vector on the unit circle.
 * @param angle the angle to transformed
 * @return the calculated vector
 */
CgalTypes::Vector map_angle_to_vector(const double &angle);

#endif //VECTORUTILS_H
