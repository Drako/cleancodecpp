cmake_minimum_required(VERSION 3.17)
cmake_policy(VERSION 3.17)
project(cleancodecpp VERSION 0.1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

enable_testing()

add_subdirectory(contrib)
add_subdirectory(examples)
