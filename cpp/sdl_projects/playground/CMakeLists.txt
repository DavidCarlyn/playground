cmake_minimum_required(VERSION 2.8)
project(playground)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")

link_directories("${PROJECT_SOURCE_DIR}/sdl/bin")
include_directories("${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}/sdl/include/SDL2")

link_directories("${PROJECT_SOURCE_DIR}/sdl_image/bin")
include_directories("${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}/sdl_image/include/SDL2")

add_executable(myMain main.cpp)
target_link_libraries(myMain mingw32 SDL2main SDL2 SDL2_image)
