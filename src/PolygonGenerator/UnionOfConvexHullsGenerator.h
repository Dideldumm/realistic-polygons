//
// Created by dideldumm on 22.02.25.
//

#ifndef UNIONOFCONVEXHULLSGENERATOR_H
#define UNIONOFCONVEXHULLSGENERATOR_H
#include <list>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Polygon_2.h>


typedef CGAL::Exact_predicates_exact_constructions_kernel Kernel;
typedef CGAL::Polygon_2<Kernel> Polygon;
typedef CGAL::Point_2<Kernel> Point;


Polygon generate_random_convex_polygon(const std::list<Point> &vertices);

Polygon unionOfConvexHulls(const unsigned int max_number_of_points, const unsigned int number_of_polygons, const double
                           max_translation_distance);


#endif //UNIONOFCONVEXHULLSGENERATOR_H
