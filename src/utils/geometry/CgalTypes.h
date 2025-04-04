//
// Created by dideldumm on 22.02.25.
//

#ifndef CGALGEOMETRY_H
#define CGALGEOMETRY_H

#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/point_generators_2.h>

namespace CgalTypes {
    typedef CGAL::Exact_predicates_exact_constructions_kernel Kernel;
    typedef CGAL::Point_2<Kernel> Point;
    typedef CGAL::Segment_2<Kernel> Segment;
    typedef CGAL::Polygon_2<Kernel> Polygon;
    typedef std::list<Point> ConvexHull;
    typedef CGAL::Vector_2<Kernel> Vector;
    typedef Kernel::FT Number;
    typedef CGAL::Random_points_in_disc_2<Point, CGAL::Creator_uniform_2<Number, Point> > PointGenerator;
}
#endif //CGALGEOMETRY_H
