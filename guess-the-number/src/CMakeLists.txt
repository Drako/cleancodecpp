add_library(GuessTheNumberImpl STATIC
    GuessTheNumber.hxx GuessTheNumber.cxx
    RandomNumberGenerator.hxx StdRandomNumberGenerator.cxx StdRandomNumberGenerator.hxx
    IODevice.hxx Console.hxx Console.cxx
    GameIO.hxx GuessTheNumberIO.hxx GuessTheNumberIO.cxx
    Result.hxx
    )
target_link_libraries(GuessTheNumberImpl PUBLIC
    staticdi)
target_include_directories(GuessTheNumberImpl INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(GuessTheNumber main.cxx)
target_link_libraries(GuessTheNumber PRIVATE
    GuessTheNumberImpl
    )
