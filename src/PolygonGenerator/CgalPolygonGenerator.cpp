//
// Created by dideldumm on 21.02.25.
//

#include "CgalPolygonGenerator.h"

#include <execution>
#include <CGAL/Random.h>
#include <CGAL/point_generators_2.h>
#include <CGAL/random_polygon_2.h>

typedef CGAL::Random_points_in_disc_2<CgalTypes::Point> Point_generator;

CgalTypes::Polygon generate_simple_polygon(const int &number_of_vertices) {
    CgalTypes::Polygon polygon;

    constexpr int radius = 1;
    std::list<CgalTypes::Point> random_points;
    CGAL::copy_n_unique(Point_generator(radius), number_of_vertices,
                        std::back_inserter(random_points));
    CGAL::random_polygon_2(random_points.size(), std::back_inserter(polygon),
                           random_points.begin());
    return polygon;
}

std::vector<CgalTypes::Polygon> generate_polygons(const int &number_of_polygons, const int &max_number_of_vertices) {
    std::vector<CgalTypes::Polygon> polygons(number_of_polygons);
    std::atomic<int> i{0};
    std::generate(std::execution::par, polygons.begin(), polygons.end(), [&]() {
        const auto thread_id = std::this_thread::get_id();
        const size_t thread_id_number = std::hash<std::thread::id>{}(thread_id);
        const long time_point = std::chrono::high_resolution_clock::now().time_since_epoch().count();
        const unsigned int seed = thread_id_number ^ time_point;
        CGAL::Random rand(seed);
        const int size = rand.get_int(4, max_number_of_vertices);
        std::cout << "Generating polygon " << i.fetch_add(1) << " of " << number_of_polygons << " with size " << size
                << " from thread with id " << thread_id << std::endl;
        return generate_simple_polygon(size);
    });
    return polygons;
}

// number of polygons 383
// max number of vertices 495
