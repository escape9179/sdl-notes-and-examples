cmake_minimum_required(VERSION 3.16)
project(SDLGame CXX)

set(CMAKE_CXX_STANDARD 14)

add_executable(SDLGame main.cpp)

find_library(SDL2 SDL2 lib)
find_library(SDL2MAIN SDL2main lib)

include_directories(include)

target_link_libraries(SDLGame ${SDL2} ${SDL2MAIN})
