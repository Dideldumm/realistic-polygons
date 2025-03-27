//
// Created by dideldumm on 23.02.25.
//

#include "./PolygonNormalizer.h"

CgalTypes::Point find_middle_point(const CgalTypes::Polygon &polygon) {
    CgalTypes::Number sum_lats(0);
    CgalTypes::Number sum_longs(0);
    for (const CgalTypes::Point &vertex: polygon.vertices()) {
        sum_lats += vertex.y();
        sum_longs += vertex.x();
    }
    sum_lats /= CgalTypes::Number(polygon.vertices().size());
    sum_longs /= CgalTypes::Number(polygon.vertices().size());
    return {sum_lats, sum_longs};
}

CgalTypes::Polygon move_to_origin(const CgalTypes::Polygon &polygon) {
    const CgalTypes::Point middle = find_middle_point(polygon);
    std::vector<CgalTypes::Point> vertices;
    for (const CgalTypes::Point &vertex: polygon.vertices()) {
        CgalTypes::Point moved_vertex(vertex.y() - middle.y(), vertex.x() - middle.x());
        vertices.emplace_back(moved_vertex);
    }
    return {vertices.begin(), vertices.end()};
}

CgalTypes::Number squared_distance(const CgalTypes::Point &a) {
    return (a.y() * a.y()) + (a.x() * a.x());
}

CgalTypes::Point find_point_furthest_from_origin(const CgalTypes::Polygon &polygon) {
    CgalTypes::Number max_distance = 0;
    CgalTypes::Point furthest_point(0, 0);
    for (const CgalTypes::Point &vertex: polygon.vertices()) {
        if (const CgalTypes::Number distance = squared_distance(vertex); distance > max_distance) {
            max_distance = distance;
            furthest_point = vertex;
        }
    }
    return furthest_point;
}

CgalTypes::Polygon normalize_scaling(const CgalTypes::Polygon &polygon) {
    const CgalTypes::Point furthest_point = find_point_furthest_from_origin(polygon);
    const CgalTypes::Number distance = squared_distance(furthest_point);
    std::vector<CgalTypes::Point> normalized_vertices;
    for (const CgalTypes::Point &vertex: polygon.vertices()) {
        CgalTypes::Point normalized_vertex(vertex.y() / distance, vertex.x() / distance);
        normalized_vertices.emplace_back(normalized_vertex);
    }
    return {normalized_vertices.begin(), normalized_vertices.end()};
}
