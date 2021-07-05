add_executable(examples
    fiddle_tests.cxx
    list.hxx list_tests.cxx
    roman_numeral_converter.cxx roman_numeral_converter.hxx roman_numeral_converter_tests.cxx
    bowling_game.cxx bowling_game.hxx bowling_game_tests.cxx)
target_link_libraries(examples PRIVATE gmock_main gtest gmock)
add_test(example_tests COMMAND examples)
