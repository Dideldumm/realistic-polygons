//
// Created by dideldumm on 05.10.24.
//

#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Polygon_2.h>

#include "../utils/VectorUtils.h"
#include "utils/geometry/PointAndSegmentUtils.h"

typedef CGAL::Exact_predicates_exact_constructions_kernel Kernel;
typedef CGAL::Segment_2<Kernel> Segment;
typedef CGAL::Polygon_2<Kernel> Polygon;
typedef Polygon PolygonalChain;

double minimum_squared_distance(const PolygonalChain &a, const PolygonalChain &b) {
    double minimum_squared_distance = std::numeric_limits<double>::max();
    for (const Segment edge_a: a.edges()) {
        for (const Segment edge_b: b.edges()) {
            if (const double squared_distance = CGAL::squared_distance(edge_a, edge_b);
                squared_distance < minimum_squared_distance) {
                minimum_squared_distance = squared_distance;
            }
        }
    }
    return minimum_squared_distance;
}

double minimum_squared_distance(const Point &a, const PolygonalChain &b) {
    double minimum_squared_distance = std::numeric_limits<double>::max();
    for (const Segment edge: b.edges()) {
        if (const double squared_distance = CGAL::squared_distance(a, edge);
            squared_distance < minimum_squared_distance) {
            minimum_squared_distance = squared_distance;
        }
    }
    return minimum_squared_distance;
}

std::pair<PolygonalChain, PolygonalChain> find_closest_polygonal_chains(
    const std::vector<PolygonalChain> &set_of_polygonal_chains) {
    std::vector<std::pair<PolygonalChain, PolygonalChain> > pairs = createAllPairs(set_of_polygonal_chains);
    double minimum_distance = std::numeric_limits<double>::max();
    std::pair<PolygonalChain, PolygonalChain> pair_of_closest_chains = pairs.front();
    for (const auto &chain_pair: pairs) {
        auto [a, b] = chain_pair;
        double squared_distance;
        if (a.size() == 1 && b.size() == 1) {
            squared_distance = CGAL::squared_distance(*a.begin(), *b.begin());
        } else if (a.size() == 1) {
            squared_distance = minimum_squared_distance(*a.begin(), b);
        } else if (b.size() == 1) {
            squared_distance = minimum_squared_distance(*b.begin(), a);
        } else {
            squared_distance = minimum_squared_distance(a, b);
        }
        if (squared_distance < minimum_distance) {
            minimum_distance = squared_distance;
            pair_of_closest_chains = chain_pair;
        }
    }
    return pair_of_closest_chains;
}

template<typename Container>
std::vector<PolygonalChain> map_points_to_polygonal_chains(const Container &points) {
    std::vector<PolygonalChain> polygonal_chains;
    for (const Point point: points) {
        PolygonalChain new_chain;
        new_chain.push_back(point);
        polygonal_chains.emplace_back(new_chain);
    }
    return polygonal_chains;
}

PolygonalChain merge_chains(const PolygonalChain &a, const PolygonalChain &b) {
    // hmm
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
    return final_chain;
}

int main(const int argc, char **argv) {
    return 0;
}
