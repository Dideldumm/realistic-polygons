cmake_minimum_required(VERSION 3.28)
project(try_cgal)

find_package(CGAL REQUIRED OPTIONAL_COMPONENTS Qt5)

set(CMAKE_CXX_STANDARD 17)

add_executable(simplePolygon
        src/GenerateSimplePolygon.cpp
        src/AlgoGeoUtils.h
        src/AlgoGeoUtils.cpp)

add_executable(shortestPolygon
        src/GenerateShortestPolygon.cpp
        src/AlgoGeoUtils.h
        src/AlgoGeoUtils.cpp)

if (CGAL_Qt5_FOUND)
    target_link_libraries(simplePolygon PUBLIC CGAL::CGAL_Basic_viewer)
	target_link_libraries(shortestPolygon PUBLIC CGAL::CGAL_Basic_viewer)
endif ()

