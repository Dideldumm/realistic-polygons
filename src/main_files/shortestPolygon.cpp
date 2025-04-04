//
// Created by dideldumm on 25.02.25.
//

#include <future>
#include <CGAL/draw_polygon_2.h>
#include <CGAL/random_polygon_2.h>

#include "../PolygonGenerator/BruteForceShortestPolygon.h"
#include "../utils/geometry/CgalTypes.h"
#include "../utils/ToStringUtils.h"

int main(const int argc, char *argv[]) {
    const int numberOfPoints = std::stoi(argv[1]);

    const CgalTypes::PointGenerator point_generator(15);
    std::vector<CgalTypes::Point> points;
    CGAL::copy_n_unique(point_generator, numberOfPoints, std::back_inserter(points));

    for (const CgalTypes::Point &point: points) {
        std::cout << pointToString(point) << std::endl;
    }
    std::cout << "And now we wait" << std::endl;
    const auto start = std::chrono::high_resolution_clock::now();
    const CgalTypes::Polygon polygon = createShortestPolygon(points);
    const auto stop = std::chrono::high_resolution_clock::now();
    const auto duration = std::chrono::duration_cast<std::chrono::seconds>(stop - start);
    std::cout << "Finished and took " << duration.count() << " seconds." << std::endl;
    std::future<void> noValue = std::async([polygon]() { CGAL::draw(polygon); });
}
