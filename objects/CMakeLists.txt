cmake_minimum_required (VERSION 3.29)

project (objects)

find_package(vsg REQUIRED)
find_package(vsgXchange REQUIRED)

set (CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} vsg::vsg vsgXchange::vsgXchange)
