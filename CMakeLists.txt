cmake_minimum_required(VERSION 3.8)

project(Euler)

file(GLOB_RECURSE SRC_FILES src/*.cpp)

add_executable(Euler ${SRC_FILES})

target_compile_features(Euler PUBLIC cxx_std_17)