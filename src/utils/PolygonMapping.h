//
// Created by dideldumm on 21.02.25.
//

#ifndef POLYGONMAPPING_H
#define POLYGONMAPPING_H


#include "geometry/CgalTypes.h"
#include "PolygonCsvWriter.h"
#include "../geojson/GeoJsonPolygon.h"


CsvWriter::Polygon map_polygon(CgalTypes::Polygon const &polygon);

CsvWriter::Polygon map_polygon(GeoJsonPolygon const &polygon);

template<typename T>
std::vector<CsvWriter::Polygon> map_polygons(const std::vector<T> &polygons) {
    std::vector<CsvWriter::Polygon> mapped_polygons;
    mapped_polygons.reserve(polygons.size());
    for (const GeoJsonPolygon &polygon: polygons) {
        mapped_polygons.push_back(map_polygon(polygon));
    }
    return mapped_polygons;
}

#endif //POLYGONMAPPING_H
