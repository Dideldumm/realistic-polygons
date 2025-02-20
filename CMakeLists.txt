cmake_minimum_required(VERSION 3.28)
project(try_cgal)

# Find necessary packages
find_package(CGAL REQUIRED OPTIONAL_COMPONENTS Qt6)
find_package(GMP REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(JSONCPP jsoncpp)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wpedantic -Wextra")

# Add executables
add_executable(simplePolygon
        src/utils/geometry/PointUtils.cpp
        src/utils/geometry/SegmentUtils.cpp
        src/utils/PointGenerator/RandomPointGenerator.cpp
        src/utils/PointGenerator/SeededPointGenerator.cpp
        src/utils/PointGenerator/RingDistributionPointGenerator.cpp
        src/PolygonGenerator/GenerateSimplePolygon.cpp
        src/utils/CommandLineArgumentHandler.cpp
)

add_executable(shortestPolygon
        src/PolygonGenerator/BruteForceShortestPolygon.cpp
        src/utils/geometry/PointUtils.cpp
        src/utils/PointGenerator/RandomPointGenerator.cpp
        src/utils/PointGenerator/SeededPointGenerator.cpp
        src/utils/PointGenerator/RingDistributionPointGenerator.cpp
        src/utils/CommandLineArgumentHandler.cpp
        src/utils/ToStringUtils.cpp
)

#add_executable(mergeClosestObjects
#        src/MergeClosestObjectsAlgorithm.cpp
#        src/utils/geometry/PointAndSegmentUtils.cpp
#        src/utils/ToStringUtils.cpp
#        src/TwoOptMoves.cpp
#        src/utils/PointGenerator/RandomPointGenerator.cpp
#        src/utils/PointGenerator/SeededPointGenerator.cpp
#        src/utils/PointGenerator/RingDistributionPointGenerator.cpp
#        src/utils/CommandLineArgumentHandler.cpp
#        src/utils/geometry/PolygonalChain.cpp
#        src/utils/geometry/PolygonalChain.h
#)

#add_executable(twoOptMoves
#        src/TwoOptMoves.cpp
#        src/utils/PointGenerator/RandomPointGenerator.cpp
#        src/utils/PointGenerator/SeededPointGenerator.cpp
#        src/utils/PointGenerator/RingDistributionPointGenerator.cpp
#        src/utils/CommandLineArgumentHandler.cpp
#        src/utils/ToStringUtils.cpp
#        src/TwoOptMovesTest.cpp
#)

add_executable(mergeConvexHulls
        src/PolygonGenerator/MergeConvexHulls.cpp
        src/utils/geometry/PolygonUtils.cpp
        src/utils/geometry/PointUtils.cpp
        src/utils/PointGenerator/RandomPointGenerator.cpp
        src/utils/PointGenerator/RingDistributionPointGenerator.cpp
        src/utils/PointGenerator/SeededPointGenerator.cpp
)

#add_executable(mergeClosestChains
#        src/MergeClosestPolygonalChainsAlgorithm.cpp
#        src/utils/geometry/PolygonalChain.cpp
#        src/utils/geometry/PolygonalChain.h
#        src/utils/VectorUtils.cpp
#        src/utils/VectorUtils.h)
#)

add_executable(test
        src/test.cpp
        src/utils/PointGenerator/SeededPointGenerator.cpp
        src/utils/PointGenerator/RingDistributionPointGenerator.cpp
        src/utils/PointGenerator/RandomPointGenerator.cpp
        src/utils/ToStringUtils.cpp
        src/utils/geometry/PolygonUtils.cpp
        src/utils/geometry/VectorUtils.cpp
)

add_executable(unionOfConvexHulls
        src/PolygonGenerator/UnionOfConvexHulls.cpp
        src/utils/PointGenerator/SeededPointGenerator.cpp
        src/utils/PointGenerator/RingDistributionPointGenerator.cpp
        src/utils/PointGenerator/RandomPointGenerator.cpp
        src/utils/ToStringUtils.cpp
        src/utils/geometry/PolygonUtils.cpp
        src/utils/geometry/VectorUtils.cpp
)

add_executable(leftMostRightmostVertices
        src/LeftMostRightMostVertices/LeftMostRightMostVertices.cpp
        src/LeftMostRightMostVertices/QuadrantTree.cpp
        src/LeftMostRightMostVertices/QuadrantTree.h
        src/utils/geometry/SegmentUtils.h
        src/utils/geometry/SegmentUtils.cpp
)

add_executable(geojsonparser
        src/geojson/geojson.cpp
        src/geojson/GeoJsonPolygon.cpp
        src/geojson/GeoJsonParser.cpp
        src/utils/PolygonCsvWriter.cpp
)

add_executable(unrealisticPolygons
        src/PolygonGenerator/unrealisticpolygons.cpp
        src/geojson/GeoJsonPolygon.cpp
        src/utils/PolygonCsvWriter.cpp
        src/utils/PointGenerator/SeededPointGenerator.cpp
        src/utils/PointGenerator/RingDistributionPointGenerator.cpp
        src/utils/PointGenerator/RandomPointGenerator.cpp
)

target_include_directories(geojsonparser PRIVATE ${JSONCPP_INCLUDE_DIRS})
target_link_libraries(geojsonparser PRIVATE ${JSONCPP_LIBRARIES})
#target_link_libraries(unrealisticPolygons PRIVATE CGAL::CGAL GMP::GMP GMP::GMPXX)

# Define a list of targets - mergeClosestObjects twoOptMoves
set(TARGETS simplePolygon shortestPolygon mergeConvexHulls test unionOfConvexHulls unrealisticPolygons)

# Link libraries if CGAL with Qt6 is found
if (CGAL_Qt6_FOUND)
    message(STATUS "CGAL with Qt6 found. Linking the viewer")
    foreach (target IN LISTS TARGETS)
        target_link_libraries(${target} PUBLIC CGAL::CGAL_Basic_viewer stdc++ m)
    endforeach ()
else ()
    # Fallback action or alternative libraries
    message(WARNING "CGAL with Qt6 not found. The viewer will not be linked.")
    foreach (target IN LISTS TARGETS)
        target_link_libraries(${target} PUBLIC stdc++ m)
    endforeach ()
endif ()
add_executable(unionedHullsGenerator src/PolygonGenerator/unionedHullsGenerator.cpp)
