//
// Created by dideldumm on 21.02.25.
//

#include "PolygonMapping.h"


typedef CGAL::Point_2<CGALKernel> CGALPoint;


CsvWriter::Point map_cgal_point(const CGALPoint &p) {
    return {CGAL::to_double(p.x()), CGAL::to_double(p.y())};
}

CsvWriter::Polygon map_polygon(CGALPolygon const &polygon) {
    CsvWriter::Polygon mapped_polygon;
    mapped_polygon.reserve(polygon.vertices().size());
    std::ranges::transform(polygon.vertices(), std::back_inserter(mapped_polygon), map_cgal_point);
    return mapped_polygon;
}

CsvWriter::Polygon map_polygon(GeoJsonPolygon const &polygon) {
    std::vector<CsvWriter::Point> mapped_vertices;
    mapped_vertices.reserve(polygon.getVertices().size());
    for (const auto &vertex: polygon.getVertices()) {
        CsvWriter::Point mapped_vertex(vertex.longitude, vertex.latitude);
        mapped_vertices.emplace_back(mapped_vertex);
    }
    return mapped_vertices;
}
