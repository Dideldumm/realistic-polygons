//
// Created by dideldumm on 22.10.24.
//

#include <CGAL/convex_hull_2.h>
#include <CGAL/Polygon_with_holes_2.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/draw_polygon_2.h>
#include <CGAL/Boolean_set_operations_2/join.h>

#include "PolygonUtils.h"

typedef CGAL::Polygon_with_holes_2<Kernel> PolygonWithHoles;
typedef CGAL::Aff_transformation_2<Kernel> Transformation;

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
    PolygonWithHoles result(polygons.at(0));
    for (unsigned int i = 1; i < polygons.size(); ++i) {
        CGAL::join(polygons.at(i), result.outer_boundary(), result);
    }
    return result.outer_boundary();
}

Polygon translate_polygon(const Polygon &polygon, const Vector &vector) {
    const Transformation translate(CGAL::TRANSLATION, vector);
    return CGAL::transform(translate, polygon);
}
