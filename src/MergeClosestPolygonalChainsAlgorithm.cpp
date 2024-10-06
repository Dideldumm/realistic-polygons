//
// Created by dideldumm on 05.10.24.
//

#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Polygon_2.h>

#include "utils/geometry/PolygonalChain.h"
#include "utils/VectorUtils.h"

std::pair<PolygonalChain, PolygonalChain> find_closest_polygonal_chains(
    const std::vector<PolygonalChain> &set_of_polygonal_chains) {
}

template<typename Container>
std::vector<PolygonalChain> map_points_to_polygonal_chains(const Container &points) {
    std::vector<PolygonalChain> polygonal_chains;
    for (const Point point: points) {
        polygonal_chains.emplace_back(point);
    }
    return polygonal_chains;
}

PolygonalChain merge_chains(const PolygonalChain &a, const PolygonalChain &b) {
    if (a.size() == 1 && b.size() == 1) {
        PolygonalChain c(a.getFirstElement());
    }
}

Polygon build_polygon(const PolygonalChain &polygonal_chain) {
    Polygon polygon;
    for (const Point point: polygonal_chain.getElements()) {
        polygon.push_back(point);
    }
    return polygon;
}

template<typename Container>
Polygon mergeClosestChainsAlgorithm(const Container &points) {
    std::vector<PolygonalChain> polygonal_chains = map_points_to_polygonal_chains(points);
    while (polygonal_chains.size() > 1) {
        auto [a, b] = find_closest_polygonal_chains(polygonal_chains);
        PolygonalChain merged = merge_chains(a, b);
        remove_element_from_vector(polygonal_chains, a);
        remove_element_from_vector(polygonal_chains, b);
        polygonal_chains.emplace_back(merged);
    }
    const PolygonalChain final_chain = polygonal_chains.front();
    return build_polygon(final_chain);
}

int main(const int argc, char **argv) {
    return 0;
}
