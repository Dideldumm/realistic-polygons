//
// Created by dideldumm on 22.10.24.
//

#include "PolygonUtils.h"

#include <CGAL/convex_hull_2.h>

ConvexHull create_convex_hull(const std::list<Point> &vertices) {
    ConvexHull new_hull;
    CGAL::convex_hull_2(vertices.begin(), vertices.end(), std::back_inserter(new_hull));
    return new_hull;
}

void insert_point_at_segment(Polygon &polygon, const Segment &segment, const Point &point) {
    //TODO unit tests
    const Point segment_end = segment.end();
    for (auto iterator = polygon.vertices_begin(); iterator != polygon.vertices_end(); ++iterator) {
        if (*iterator == segment_end) {
            polygon.insert(iterator, point);
            break;
        }
    }
}
