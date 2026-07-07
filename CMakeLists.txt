cmake_minimum_required(VERSION 3.16)
project(VectorClass CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Strict warnings — treat your compiler as a code reviewer
add_compile_options(-Wall -Wextra -Wpedantic)

# --- Main executable ---
add_executable(main
    main.cpp
    stats.cpp
)

