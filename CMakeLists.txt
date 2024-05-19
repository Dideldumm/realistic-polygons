cmake_minimum_required(VERSION 3.28)
project(try_cgal)

find_package(CGAL REQUIRED OPTIONAL_COMPONENTS Qt5)

set(CMAKE_CXX_STANDARD 17)

add_executable(main main.cpp)

if (CGAL_Qt5_FOUND)
	target_link_libraries(main PUBLIC CGAL::CGAL_Basic_viewer)
endif()

