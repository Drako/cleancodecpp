cmake_minimum_required(VERSION 3.12)
cmake_policy(VERSION 3.12)
project(cleancodecpp VERSION 0.1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

enable_testing()

add_subdirectory(guess-the-number)
add_subdirectory(gilded-rose)
