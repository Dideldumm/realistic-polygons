//
// Created by dideldumm on 19.09.24.
//

#include <CGAL/convex_hull_2.h>
#include <CGAL/draw_polygon_2.h>

#include "MergeConvexHulls.h"

#include "../utils/geometry/SegmentUtils.h"
#include "../utils/geometry/PolygonUtils.h"
#include "../utils/geometry/CgalTypes.h"


std::list<CgalTypes::ConvexHull> build_convex_hulls(std::list<CgalTypes::Point> points) {
    std::list<CgalTypes::ConvexHull> convex_hulls;
    while (!points.empty()) {
        const CgalTypes::ConvexHull new_hull = create_convex_hull(points);
        convex_hulls.emplace_back(new_hull);
        for (const CgalTypes::Point& point: new_hull) {
            points.remove(point);
        }
    }
    return convex_hulls;
}

void merge(CgalTypes::Polygon &polygon, const CgalTypes::ConvexHull &new_hull) {
    for (const CgalTypes::Point& point: new_hull) {
        const CgalTypes::Segment nearest_segment = find_nearest_segment(polygon.edges(), point);
        insert_point_at_segment(polygon, nearest_segment, point);
    }
}

CgalTypes::Polygon merge_convex_hulls_algorithm(const std::list<CgalTypes::Point> &vertices) {
    std::list<CgalTypes::ConvexHull> convex_hulls = build_convex_hulls(vertices);
    if (convex_hulls.empty()) {
        std::cout << "Houston wir haben ein Problem!" << std::endl;
    }
    CgalTypes::ConvexHull initial_hull = convex_hulls.front();
    convex_hulls.pop_front();
    CgalTypes::Polygon polygon(initial_hull.begin(), initial_hull.end());
    while (!convex_hulls.empty()) {
        CgalTypes::ConvexHull new_hull = convex_hulls.front();
        convex_hulls.pop_front();
        merge(polygon, new_hull);
    }
    return polygon;
}

