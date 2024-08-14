cmake_minimum_required (VERSION 3.8)

project (bobbyvsg)

find_package(vsg REQUIRED)
find_package(vsgXchange REQUIRED)

file(GLOB SOURCE "src/main.cpp")
add_executable(${PROJECT_NAME} ${SOURCE})
set_target_properties (${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set_target_properties (${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)

target_link_libraries(${PROJECT_NAME} vsg::vsg vsgXchange::vsgXchange)
