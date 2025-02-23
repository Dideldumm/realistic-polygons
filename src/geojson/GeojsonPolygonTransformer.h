//
// Created by dideldumm on 23.02.25.
//

#ifndef GEOJSONPOLYGONTRANSFORMER_H
#define GEOJSONPOLYGONTRANSFORMER_H

#include "GeoJsonPolygon.h"

LatsAndLongs find_middle_point(const GeoJsonPolygon &polygon);

GeoJsonPolygon move_to_origin(const GeoJsonPolygon &polygon);

LatsAndLongs find_point_furthest_from_origin(const GeoJsonPolygon &polygon);

GeoJsonPolygon normalize_scaling(const GeoJsonPolygon &polygon);


#endif //GEOJSONPOLYGONTRANSFORMER_H
