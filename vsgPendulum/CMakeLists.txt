cmake_minimum_required (VERSION 3.29)

project (vsgPendulum)

find_package(vsg REQUIRED)
find_package(vsgXchange REQUIRED)

set (CMAKE_CXX_STANDARD 17)

# add_executable(${PROJECT_NAME} src/main.cpp)

# Add all c source files under the src directory
file(GLOB SOURCES "src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} vsg::vsg vsgXchange::vsgXchange)
