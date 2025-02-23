cmake_minimum_required(VERSION 3.28)
project(realistic-polygons)

# Find necessary packages
find_package(CGAL REQUIRED OPTIONAL_COMPONENTS Qt6)
find_package(GMP REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(JSONCPP jsoncpp)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wpedantic -Wextra")

# Collect source files
file(GLOB_RECURSE GEOJSON_SRC src/geojson/*)
file(GLOB_RECURSE POINTGENS_SRC src/utils/PointGenerator/*)
file(GLOB_RECURSE GEOMETRY_SRC src/utils/geometry/*)

source_group(TREE ${CMAKE_SOURCE_DIR}/src/geojson PREFIX "Geojson Source Files" FILES ${GEOJSON_SRC})
source_group(TREE ${CMAKE_SOURCE_DIR}/src/utils/PointGenerator PREFIX "Point Generators Source Files" FILES ${POINTGENS_SRC})
source_group(TREE ${CMAKE_SOURCE_DIR}/src/utils/geometry PREFIX "CGAL Geometry utils Source Files" FILES ${GEOMETRY_SRC})
source_group("CSV Writer Source Files" FILES
        src/utils/PolygonCsvWriter.cpp
        src/utils/PolygonCsvWriter.h
        src/utils/PolygonMapping.cpp
        src/utils/PolygonMapping.h
)

# Add executables
add_executable(simplePolygon
        src/utils/geometry/PointUtils.cpp
        src/utils/geometry/SegmentUtils.cpp
        ${POINTGENS_SRC}
        src/PolygonGenerator/GenerateSimplePolygon.cpp
)

add_executable(shortestPolygon
        src/PolygonGenerator/BruteForceShortestPolygon.cpp
        src/utils/geometry/PointUtils.cpp
        ${POINTGENS_SRC}
        src/utils/ToStringUtils.cpp
)

add_executable(mergeConvexHulls
        src/PolygonGenerator/MergeConvexHulls.cpp
        src/utils/geometry/PolygonUtils.cpp
        src/utils/geometry/PointUtils.cpp
        ${POINTGENS_SRC}
)

add_executable(unionOfConvexHulls
        src/PolygonGenerator/UnionOfConvexHulls.cpp
        ${POINTGENS_SRC}
        src/utils/ToStringUtils.cpp
        src/utils/geometry/PolygonUtils.cpp
        src/utils/geometry/VectorUtils.cpp
        src/PolygonGenerator/UnionOfConvexHullsGenerator.cpp
        src/PolygonGenerator/UnionOfConvexHullsGenerator.h
)

add_executable(leftMostRightmostVertices
        src/LeftMostRightMostVertices/LeftMostRightMostVertices.cpp
        src/LeftMostRightMostVertices/QuadrantTree.cpp
        src/utils/geometry/SegmentUtils.cpp
)

add_executable(geojsonparser
        src/geojson/geojson.cpp
        src/geojson/GeoJsonPolygon.cpp
        src/geojson/GeoJsonParser.cpp
        src/utils/PolygonCsvWriter.cpp
        src/utils/PolygonMapping.cpp
        src/geojson/GeojsonPolygonTransformer.cpp
)

add_executable(unrealisticPolygons
        src/unrealisticpolygons.cpp
        src/geojson/GeoJsonPolygon.cpp
        src/utils/PolygonCsvWriter.cpp
        ${POINTGENS_SRC}
        src/PolygonGenerator/CgalPolygonGenerator.cpp
)

add_executable(unionedHullsGenerator
        src/unionedHullsGenerator.cpp)

add_executable(polygonGenerator
        src/PolygonGenerator/PolygonGenerator.cpp
        src/utils/PolygonMapping.cpp
)

target_include_directories(geojsonparser PRIVATE ${JSONCPP_INCLUDE_DIRS})
target_link_libraries(geojsonparser PRIVATE ${JSONCPP_LIBRARIES})
#target_link_libraries(unrealisticPolygons PRIVATE CGAL::CGAL GMP::GMP GMP::GMPXX)

# Define a list of targets - mergeClosestObjects twoOptMoves
set(TARGETS simplePolygon shortestPolygon mergeConvexHulls unionOfConvexHulls unrealisticPolygons)

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

