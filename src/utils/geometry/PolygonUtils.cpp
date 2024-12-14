//
// Created by dideldumm on 22.10.24.
//

#include <CGAL/convex_hull_2.h>
#include <CGAL/Polygon_with_holes_2.h>
#include "PolygonUtils.h"

#include <CGAL/Boolean_set_operations_2/join.h>

typedef CGAL::Polygon_with_holes_2<Kernel> PolygonWithHoles;

ConvexHull create_convex_hull(const std::list<Point> &vertices) {
    ConvexHull new_hull;
    CGAL::convex_hull_2(vertices.begin(), vertices.end(), std::back_inserter(new_hull));
    return new_hull;
}

void insert_point_at_segment(Polygon &polygon, const Segment &segment, const Point &point) {
    //TODO unit test
    const Point segment_end = segment.end();
    for (auto iterator = polygon.vertices_begin(); iterator != polygon.vertices_end(); ++iterator) {
        if (*iterator == segment_end) {
            polygon.insert(iterator, point);
            break;
        }
    }
}

Polygon join_polygons(const std::vector<Polygon> &polygons) {
    //TODO unit test
    PolygonWithHoles result;
    for (const Polygon &polygon: polygons) {
        CGAL::join(polygon, result, result);
    }
    return result.outer_boundary();
}
