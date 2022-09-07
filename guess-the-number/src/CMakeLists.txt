add_library(GuessTheNumberImpl STATIC
    GuessTheNumber.hxx GuessTheNumber.cxx
    )
target_include_directories(GuessTheNumberImpl INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(GuessTheNumber main.cxx)
target_link_libraries(GuessTheNumber PRIVATE
    GuessTheNumberImpl
    staticdi
    )
