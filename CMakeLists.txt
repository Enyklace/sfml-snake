cmake_minimum_required(VERSION 3.16)

set(PROJECT_NAME "sfml-snake")

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

project(${PROJECT_NAME})

find_package(SFML 2.5 COMPONENTS graphics system window REQUIRED)

file(GLOB_RECURSE src_files ${SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE hdr_files ${SOURCE_DIR}/*.hpp)

add_executable(${PROJECT_NAME} ${src_files} ${hdr_files})
target_include_directories(${PROJECT_NAME} PUBLIC ${SOURCE_DIR})
target_link_libraries(
    ${PROJECT_NAME}
    sfml-graphics
    sfml-system
    sfml-window
)
