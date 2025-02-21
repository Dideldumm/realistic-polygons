//
// Created by dideldumm on 21.02.25.
//

#ifndef CGALPOLYGONGENERATOR_H
#define CGALPOLYGONGENERATOR_H

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polygon_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef CGAL::Polygon_2<Kernel> CGALPolygon;

CGALPolygon generate_simple_polygon(const int &number_of_vertices);

std::vector<CGALPolygon> generate_polygons(const int & number_of_polygons, const int &max_number_of_vertices);


#endif //CGALPOLYGONGENERATOR_H
