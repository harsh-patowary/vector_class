cmake_minimum_required(VERSION 3.16)
project(VectorClass CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Strict warnings — treat your compiler as a code reviewer
add_compile_options(-Wall -Wextra -Wpedantic)

#Define an INTERFACE library instead of an executable
add_library(VectorClass INTERFACE)

target_include_directories(VectorClass INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)

# --- Main executable ---
# add_executable(main
#     main.cpp
#     stats.cpp
# )

