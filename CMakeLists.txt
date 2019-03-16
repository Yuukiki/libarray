cmake_minimum_required(VERSION 2.8)
project(libarray C)

set(CMAKE_C_STANDARD 99)
add_compile_options(-std=c99)
set(SRCS array.c arraylog.c)

include_directories(
    ./include
)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
add_library(array STATIC ${SRCS})
