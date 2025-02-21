//
// Created by dideldumm on 21.02.25.
//

#ifndef POLYGONMAPPING_H
#define POLYGONMAPPING_H

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polygon_2.h>

#include "../utils/PolygonCsvWriter.h"
#include "../geojson/GeoJsonPolygon.h"


typedef CGAL::Exact_predicates_inexact_constructions_kernel CGALKernel;
typedef CGAL::Polygon_2<CGALKernel> CGALPolygon;


CsvWriter::Polygon map_polygon(CGALPolygon const &polygon);

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
