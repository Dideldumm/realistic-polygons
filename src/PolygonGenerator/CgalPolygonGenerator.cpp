//
// Created by dideldumm on 21.02.25.
//

#include "CgalPolygonGenerator.h"

#include <execution>

#include <CGAL/Random.h>
#include <CGAL/point_generators_2.h>
#include <CGAL/random_polygon_2.h>

#define CGAL_DONT_SHUFFLE_IN_RANDOM_POLYGON_2CGAL_DONT_SHUFFLE_IN_RANDOM_POLYGON_2

typedef CGAL::Random_points_in_disc_2<CgalTypes::Point> Point_generator;
typedef std::list<CgalTypes::Point> Vertices;

CgalTypes::Polygon generate_simple_polygon(const int &number_of_vertices) {
    CgalTypes::Polygon polygon;

    constexpr int radius = 1;
    CGAL::random_polygon_2(number_of_vertices, std::back_inserter(polygon),
                           Point_generator(radius));
    return polygon;
}

std::vector<Vertices> generate_vertices_for_polygons(
    const int &max_number_of_vertices, const int &number_of_polygons) {
    CGAL::Random rand;
    std::vector<Vertices> generated_polygon_vertices(number_of_polygons);
    std::ranges::generate(generated_polygon_vertices, [&]() {
        const int size = rand.get_int(4, max_number_of_vertices);
        Vertices vertices;
        CGAL::copy_n_unique(Point_generator(1), size, std::back_inserter(vertices));
        return vertices;
    });
    return generated_polygon_vertices;
}

std::vector<CgalTypes::Polygon> generate_polygons(const int &number_of_polygons, const int &max_number_of_vertices) {
    // std::vector<CgalTypes::Polygon> polygons(number_of_polygons);
    std::atomic i{0};

    std::vector<Vertices> generated_polygon_vertices = generate_vertices_for_polygons(
        max_number_of_vertices, number_of_polygons);




    std::vector<CgalTypes::Polygon> generated_polygons(number_of_polygons);
    std::transform(std::execution::par, generated_polygon_vertices.begin(), generated_polygon_vertices.end(),
                   generated_polygons.begin(), [&](Vertices &vertices) {
                       CgalTypes::Polygon polygon;
                       const int current_iteration = i.fetch_add(1);
                       const auto start_time = std::chrono::high_resolution_clock::now();
                       std::cout << "Start polygon " << current_iteration << " of " << number_of_polygons <<
                               " with size " << vertices.size() << " at time " << start_time << std::endl;

                       CGAL::random_polygon_2(vertices.size(), std::back_inserter(polygon),
                                              vertices.begin());

                       const auto end_time = std::chrono::high_resolution_clock::now();
                       const auto duration = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time);
                       std::cout << "Polygon " << current_iteration << " finished at " << end_time << " it took " <<
                               duration << std::endl;

                       return polygon;
                   });

    // std::generate(std::execution::par, polygons.begin(), polygons.end(), [&]() {
    //     const auto thread_id = std::this_thread::get_id();
    //     const size_t thread_id_number = std::hash<std::thread::id>{}(thread_id);
    //     const auto start_time = std::chrono::high_resolution_clock::now();
    //     const unsigned int seed = thread_id_number ^ start_time.time_since_epoch().count();
    //     CGAL::Random rand(seed);
    //     const int size = rand.get_int(4, max_number_of_vertices);
    //
    //     const int current_iteration = i.fetch_add(1);
    //     std::cout << "Start polygon " << current_iteration << " of " << number_of_polygons << " with size " <<
    //             size <<
    //             " at time " << start_time << std::endl;
    //
    //     CgalTypes::Polygon polygon = generate_simple_polygon(size);
    //
    //     const auto end_time = std::chrono::high_resolution_clock::now();
    //     const auto duration = std::chrono::duration_cast<std::chrono::seconds>(
    //         end_time - start_time);
    //     std::cout << "Polygon " << current_iteration << " finished at " << end_time << " it took " << duration
    //             << std::endl;
    //
    //     return polygon;
    // });
    return generated_polygons;
}

// number of polygons 383
// max number of vertices 495
