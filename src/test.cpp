//
// Created by dideldumm on 19.10.24.
//


#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Random_polygon_2_sweep.h>
#include <fstream>

using Kernel = CGAL::Exact_predicates_exact_constructions_kernel;
using FT = Kernel::FT;
using Point_2 = Kernel::Point_2;

int main(int argc, char **argv) {
    std::vector<Point_2> points;
    std::ifstream ifile(argv[1]);

    FT x, y;
    while (ifile >> CGAL::iformat(x) >> CGAL::iformat(y))
        points.emplace_back(x, y);
    std::cerr << points.size() << " points read" << std::endl;

    CGAL::make_simple_polygon(points.begin(), points.end(), Kernel());

    return EXIT_SUCCESS;
}
