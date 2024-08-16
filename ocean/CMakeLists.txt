cmake_minimum_required (VERSION 3.29)

project (ocean)

find_package(vsg REQUIRED)
find_package(vsgXchange REQUIRED)

set (CMAKE_CXX_STANDARD 17)

add_executable(ocean src/main.cpp)
target_link_libraries(ocean vsg::vsg vsgXchange::vsgXchange)
