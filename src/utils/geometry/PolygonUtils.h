//
// Created by dideldumm on 22.10.24.
//

#ifndef POLYGONUTILS_H
#define POLYGONUTILS_H

#include <CGAL/Polygon_2.h>

#include "CgalTypes.h"


CgalTypes::ConvexHull create_convex_hull(const std::list<CgalTypes::Point> &vertices);

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
void insert_point_at_segment(CgalTypes::Polygon &polygon, const CgalTypes::Segment &segment,
                             const CgalTypes::Point &point);

CgalTypes::Polygon join_polygons(const std::vector<CgalTypes::Polygon> &polygons);

CgalTypes::Polygon translate_polygon(const CgalTypes::Polygon &polygon, const CgalTypes::Vector &vector);

#endif //POLYGONUTILS_H
