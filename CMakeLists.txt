cmake_minimum_required(VERSION 3.20)
cmake_policy(VERSION 3.20)
project(cleancodecpp VERSION 0.1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)
FetchContent_Declare(
    GoogleTest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG 58d77fa8070e8cec2dc1ed015d66b454c8d78850 # release-1.12.1
)
FetchContent_Declare(
    StaticDI
    GIT_REPOSITORY https://github.com/Drako/staticdi.git
    GIT_TAG 1a02830a879e63a8d8d318ef2473f178ed2b301e
)
FetchContent_MakeAvailable(GoogleTest StaticDI)

enable_testing()

add_subdirectory(guess-the-number)
add_subdirectory(gilded-rose)
