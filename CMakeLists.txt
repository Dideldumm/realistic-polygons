cmake_minimum_required(VERSION 3.28)
project(realistic-polygons)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wpedantic -Wextra")

# Set path to dependencies
set(CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/lib" ${CMAKE_PREFIX_PATH})
set(CMAKE_LIBRARY_PATH "${CMAKE_SOURCE_DIR}/lib" ${CMAKE_LIBRARY_PATH})
set(CMAKE_INCLUDE_PATH "${CMAKE_SOURCE_DIR}/include" ${CMAKE_INCLUDE_PATH})

# Find necessary packages
link_directories(${CMAKE_SOURCE_DIR}/lib)
include_directories(${CMAKE_SOURCE_DIR}/include)

find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(CGAL REQUIRED OPTIONAL_COMPONENTS Qt6)
find_package(GMP REQUIRED)
find_package(TBB REQUIRED)

# Collect source files and group them
file(GLOB_RECURSE GEOJSON_SRC src/geojson/*)
file(GLOB_RECURSE GEOMETRY_SRC src/utils/geometry/*)

source_group(TREE ${CMAKE_SOURCE_DIR}/src/geojson PREFIX "Geojson Source Files" FILES ${GEOJSON_SRC})
source_group(TREE ${CMAKE_SOURCE_DIR}/src/utils/PointGenerator PREFIX "Point Generators Source Files" FILES ${POINTGENS_SRC})
source_group(TREE ${CMAKE_SOURCE_DIR}/src/utils/geometry PREFIX "CGAL Geometry utils Source Files" FILES ${GEOMETRY_SRC})
source_group("CSV Writer Source Files" FILES
        src/InputOutput/PolygonCsvWriter.cpp
        src/InputOutput/PolygonCsvWriter.h
)

# Add executables
add_executable(simplePolygon
        src/PolygonGenerator/GenerateSimplePolygon.cpp
        src/utils/geometry/PointUtils.cpp
        src/utils/geometry/SegmentUtils.cpp
        src/main_files/simplePolygon.cpp
)

add_executable(shortestPolygon
        src/PolygonGenerator/BruteForceShortestPolygon.cpp
        src/utils/geometry/PointUtils.cpp
        src/utils/ToStringUtils.cpp
        src/main_files/shortestPolygon.cpp
)

add_executable(mergeConvexHulls
        src/main_files/mergeConvexHulls.cpp
        src/PolygonGenerator/MergeConvexHulls.cpp
        src/utils/geometry/PolygonUtils.cpp
        src/utils/geometry/PointUtils.cpp
)

add_executable(drawUnionOfConvexHulls
        src/main_files/drawUnionOfConvexHulls.cpp
        src/utils/ToStringUtils.cpp
        src/utils/geometry/PolygonUtils.cpp
        src/utils/geometry/PolygonNormalizer.cpp
        src/utils/geometry/VectorUtils.cpp
        src/PolygonGenerator/UnionOfConvexHullsGenerator.cpp
)

add_executable(geojsonparser
        src/main_files/geojson.cpp
        src/InputOutput/GeoJsonParser.cpp
        src/InputOutput/PolygonCsvWriter.cpp
        src/utils/geometry/PolygonNormalizer.cpp
)

add_executable(unrealisticPolygons
        src/main_files/unrealisticpolygons.cpp
        src/InputOutput/PolygonCsvWriter.cpp
        src/PolygonGenerator/CgalPolygonGenerator.cpp
        src/utils/geometry/PolygonNormalizer.cpp
)

add_executable(writeUnionedHullsToFile
        src/main_files/writeUnionedHullsToFile.cpp
        src/InputOutput/PolygonCsvWriter.cpp
        src/utils/geometry/PolygonNormalizer.cpp
        src/PolygonGenerator/UnionOfConvexHullsGenerator.cpp
        src/utils/geometry/PolygonUtils.cpp
        src/InputOutput/PolygonImageSaver.cpp
        src/InputOutput/PolygonImageSaver.h
)

add_executable(polygonGenerator
        src/PolygonGenerator/PolygonGenerator.cpp
        src/InputOutput/PolygonCsvWriter.cpp
        src/InputOutput/GeoJsonParser.cpp
        src/PolygonGenerator/CgalPolygonGenerator.cpp
)

add_executable(loadPolygonPredictions
        src/InputOutput/WrittenPolygonLoader.cpp
        src/main_files/LoadPolygonPredictions.cpp
)

target_include_directories(geojsonparser PRIVATE ${JSONCPP_INCLUDE_DIRS})
target_link_libraries(geojsonparser PRIVATE ${JSONCPP_LIBRARIES})

target_include_directories(polygonGenerator PRIVATE ${JSONCPP_INCLUDE_DIRS})
target_link_libraries(polygonGenerator PRIVATE ${JSONCPP_LIBRARIES})


# Define a list of targets - mergeClosestObjects twoOptMoves
set(TARGETS
        simplePolygon
        shortestPolygon
        mergeConvexHulls
        drawUnionOfConvexHulls
        unrealisticPolygons
        geojsonparser
        writeUnionedHullsToFile
        polygonGenerator
        loadPolygonPredictions
)

# Link libraries if CGAL with Qt6 is found
if (CGAL_Qt6_FOUND)
    message(STATUS "CGAL with Qt6 found. Linking the viewer")
    foreach (target IN LISTS TARGETS)
        target_link_libraries(${target} PUBLIC CGAL::CGAL_Basic_viewer stdc++ m TBB::tbb)
    endforeach ()
else ()
    # Fallback action or alternative libraries
    message(WARNING "CGAL with Qt6 not found. The viewer will not be linked.")
    foreach (target IN LISTS TARGETS)
        target_link_libraries(${target} PUBLIC stdc++ m)
    endforeach ()
endif ()

