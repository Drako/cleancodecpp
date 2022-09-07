add_executable(GuessTheNumberTests
    GuessTheNumberTest.cxx
    )
target_link_libraries(GuessTheNumberTests PRIVATE
    GuessTheNumberImpl
    gtest gmock gmock_main
    )

add_test(NAME GuessTheNumberTests COMMAND GuessTheNumberTests)
