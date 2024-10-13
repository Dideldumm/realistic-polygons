cmake_minimum_required(VERSION 3.28)
project(try_cgal)

# Find necessary packages
find_package(CGAL REQUIRED OPTIONAL_COMPONENTS Qt6)
find_package(GMP REQUIRED)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wpedantic -Wextra")

# Add executables
add_executable(simplePolygon
        src/utils/geometry/PointAndSegmentUtils.cpp
        src/utils/RandomPointGenerator.cpp
        src/GenerateSimplePolygon.cpp
        src/utils/CommandLineArgumentHandler.cpp
)

add_executable(shortestPolygon
        src/GenerateShortestPolygon.cpp
        src/utils/geometry/PointAndSegmentUtils.cpp
        src/utils/RandomPointGenerator.cpp
        src/utils/CommandLineArgumentHandler.cpp
        src/utils/ToStringUtils.cpp
)

add_executable(mergeClosestObjects
        src/MergeClosestObjectsAlgorithm.cpp
        src/utils/geometry/PointAndSegmentUtils.cpp
        src/utils/ToStringUtils.cpp
        src/TwoOptMoves.cpp
        src/utils/RandomPointGenerator.cpp
        src/utils/CommandLineArgumentHandler.cpp
        src/utils/geometry/PolygonalChain.cpp
        src/utils/geometry/PolygonalChain.h
)

add_executable(twoOptMoves
        src/TwoOptMoves.cpp
        src/utils/RandomPointGenerator.cpp
        src/utils/CommandLineArgumentHandler.cpp
        src/utils/ToStringUtils.cpp
        src/TwoOptMovesTest.cpp
)

add_executable(mergeConvexHulls
        src/MergeConvexHulls.cpp)

add_executable(mergeClosestChains
        src/MergeClosestPolygonalChainsAlgorithm.cpp
        src/utils/geometry/PolygonalChain.cpp
        src/utils/geometry/PolygonalChain.h
        src/utils/VectorUtils.cpp
        src/utils/VectorUtils.h)

# Define a list of targets
set(TARGETS simplePolygon shortestPolygon mergeClosestObjects twoOptMoves)

# Link libraries if CGAL with Qt6 is found
if (CGAL_Qt6_FOUND)
    foreach (target IN LISTS TARGETS)
        target_link_libraries(${target} PUBLIC CGAL::CGAL_Basic_viewer stdc++ m)
    endforeach ()
else ()
    # Fallback action or alternative libraries
    message(WARNING "CGAL with Qt5 not found. The viewer will not be linked.")
    foreach (target IN LISTS TARGETS)
        target_link_libraries(${target} PUBLIC stdc++ m)
    endforeach ()
endif ()

