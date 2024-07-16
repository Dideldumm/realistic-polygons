cmake_minimum_required(VERSION 3.28)
project(try_cgal)

find_package(CGAL REQUIRED OPTIONAL_COMPONENTS Qt5)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wpedantic -Wextra")

add_executable(simplePolygon
        src/utils/AlgoGeoUtils.cpp
        src/utils/RandomPointGenerator.cpp
        src/GenerateSimplePolygon.cpp
        src/utils/CommandLineArgumentHandler.h
        src/utils/CommandLineArgumentHandler.cpp)

add_executable(shortestPolygon
        src/GenerateShortestPolygon.cpp
        src/utils/AlgoGeoUtils.cpp
        src/utils/RandomPointGenerator.cpp
        src/utils/CommandLineArgumentHandler.h
        src/utils/CommandLineArgumentHandler.cpp)

if (CGAL_Qt5_FOUND)
    target_link_libraries(simplePolygon PUBLIC CGAL::CGAL_Basic_viewer)
    target_link_libraries(shortestPolygon PUBLIC CGAL::CGAL_Basic_viewer)
endif ()

