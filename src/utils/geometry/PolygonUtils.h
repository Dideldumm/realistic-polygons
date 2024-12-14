//
// Created by dideldumm on 22.10.24.
//

#ifndef POLYGONUTILS_H
#define POLYGONUTILS_H

#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Polygon_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef CGAL::Point_2<Kernel> Point;
typedef CGAL::Segment_2<Kernel> Segment;
typedef CGAL::Polygon_2<Kernel> Polygon;
typedef std::list<Point> ConvexHull;

ConvexHull create_convex_hull(const std::list<Point> &vertices);

/**
 * Inserts the given point into the given polygon at the position of the given segment.
 *
 * If the polygon does contain the given segment, the new point will be inserted before the endpoint of the segment.<br>
 * If the polygon does <b>not</b> contain the given segment, the new point will <b>not</b> be inserted.
 *
 * @param polygon the polygon where the point is inserted
 * @param segment the position where the point should be inserted into the polygon
 * @param point the point that should be inserted
 */
void insert_point_at_segment(Polygon &polygon, const Segment &segment, const Point &point);

Polygon join_polygons(const std::vector<Polygon> & polygons);

void trans

#endif //POLYGONUTILS_H
