//
// Created by dideldumm on 23.02.25.
//

#ifndef GEOJSONPOLYGONTRANSFORMER_H
#define GEOJSONPOLYGONTRANSFORMER_H
#include "CgalTypes.h"


CgalTypes::Point find_middle_point(const CgalTypes::Polygon &polygon);

CgalTypes::Polygon move_to_origin(const CgalTypes::Polygon &polygon);

CgalTypes::Point find_point_furthest_from_origin(const CgalTypes::Polygon &polygon);

CgalTypes::Polygon normalize_scaling(const CgalTypes::Polygon &polygon);


#endif //GEOJSONPOLYGONTRANSFORMER_H
