//
// Created by dideldumm on 23.02.25.
//

#include "GeojsonPolygonTransformer.h"

LatsAndLongs find_middle_point(const GeoJsonPolygon &polygon) {
    double sum_lats = 0;
    double sum_longs = 0;
    for (const LatsAndLongs &vertex: polygon.getVertices()) {
        sum_lats += vertex.latitude;
        sum_longs += vertex.longitude;
    }
    sum_lats /= polygon.getVertices().size();
    sum_longs /= polygon.getVertices().size();
    return LatsAndLongs(sum_lats, sum_longs);
}

GeoJsonPolygon move_to_origin(const GeoJsonPolygon &polygon) {
    const LatsAndLongs middle = find_middle_point(polygon);
    std::vector<LatsAndLongs> vertices;
    for (const LatsAndLongs &vertex: polygon.getVertices()) {
        LatsAndLongs moved_vertex(vertex.latitude - middle.latitude, vertex.longitude - middle.longitude);
        vertices.emplace_back(moved_vertex);
    }
    return GeoJsonPolygon(vertices);
}

double squared_distance(const LatsAndLongs &a) {
    return (a.latitude * a.latitude) + (a.longitude * a.longitude);
}

LatsAndLongs find_point_furthest_from_origin(const GeoJsonPolygon &polygon) {
    double max_distance = 0;
    LatsAndLongs furthest_point(0, 0);
    for (const LatsAndLongs &vertex: polygon.getVertices()) {
        if (const double distance = squared_distance(vertex); distance > max_distance) {
            max_distance = distance;
            furthest_point = vertex;
        }
    }
    return furthest_point;
}

GeoJsonPolygon normalize_scaling(const GeoJsonPolygon &polygon) {
    const LatsAndLongs furthest_point = find_point_furthest_from_origin(polygon);
    const double distance = squared_distance(furthest_point);
    std::vector<LatsAndLongs> normalized_vertices;
    for (const LatsAndLongs &vertex: polygon.getVertices()) {
        LatsAndLongs normalized_vertex(vertex.latitude / distance, vertex.longitude / distance);
        normalized_vertices.emplace_back(normalized_vertex);
    }
    return GeoJsonPolygon(normalized_vertices);
}
