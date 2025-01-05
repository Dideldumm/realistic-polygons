//
// Created by dideldumm on 05.01.25.
//

#ifndef QUADRANTTREE_H
#define QUADRANTTREE_H

#include <CGAL/Exact_predicates_exact_constructions_kernel.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel Kernel;
typedef CGAL::Point_2<Kernel> Point;

class QuadrantTree {
private:
    QuadrantTree *top_left;
    QuadrantTree *top_right;
    QuadrantTree *bottom_left;
    QuadrantTree *bottom_right;

public:
    explicit QuadrantTree(std::vector<Point> points);
};


#endif //QUADRANTTREE_H
