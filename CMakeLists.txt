cmake_minimum_required(VERSION 3.16)
project(SDLGame CXX)

set(CMAKE_CXX_STANDARD 14)

add_executable(SDLGame 10_color_keying/10_color_keying.cpp)

find_library(SDL2 SDL2 lib)
find_library(SDL2MAIN SDL2main lib)
find_library(SDL2IMAGE SDL2_image lib)

include_directories(include/SDL)

target_link_libraries(SDLGame ${SDL2} ${SDL2MAIN} ${SDL2IMAGE})
