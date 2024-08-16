cmake_minimum_required(VERSION 3.28)
project(try_cgal)

# Find necessary packages
find_package(CGAL REQUIRED OPTIONAL_COMPONENTS Qt5)
find_package(GMP REQUIRED)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wpedantic -Wextra")

# Add executables
add_executable(simplePolygon
        src/utils/AlgoGeoUtils.cpp
        src/utils/RandomPointGenerator.cpp
        src/GenerateSimplePolygon.cpp
        src/utils/CommandLineArgumentHandler.cpp)

add_executable(shortestPolygon
        src/GenerateShortestPolygon.cpp
        src/utils/AlgoGeoUtils.cpp
        src/utils/RandomPointGenerator.cpp
        src/utils/CommandLineArgumentHandler.cpp)

add_executable(mergeClosestObjects
        src/MergeClosestObjectsAlgorithm.cpp
        src/utils/AlgoGeoUtils.cpp)

# Link libraries if CGAL with Qt5 is found
if (CGAL_Qt5_FOUND)
    target_link_libraries(simplePolygon PUBLIC CGAL::CGAL_Basic_viewer stdc++ m)
    target_link_libraries(shortestPolygon PUBLIC CGAL::CGAL_Basic_viewer stdc++ m)
    target_link_libraries(mergeClosestObjects PUBLIC CGAL::CGAL_Basic_viewer stdc++ m)
endif ()
