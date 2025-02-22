//
// Created by dideldumm on 22.02.25.
//

#ifndef CGALGEOMETRY_H
#define CGALGEOMETRY_H

#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Polygon_2.h>

namespace CgalTypes {
    typedef CGAL::Exact_predicates_exact_constructions_kernel Kernel;
    typedef CGAL::Point_2<Kernel> Point;
    typedef CGAL::Segment_2<Kernel> Segment;
    typedef CGAL::Polygon_2<Kernel> Polygon;
    typedef std::list<Point> ConvexHull;
    typedef CGAL::Vector_2<Kernel> Vector;
}
#endif //CGALGEOMETRY_H
