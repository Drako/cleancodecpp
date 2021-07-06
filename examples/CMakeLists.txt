add_executable(examples
    fiddle_tests.cxx
    list.hxx list_tests.cxx
    roman_numeral_converter.cxx roman_numeral_converter.hxx roman_numeral_converter_tests.cxx
    bowling_game.cxx bowling_game.hxx bowling_game_tests.cxx
    compile_time_fizzbuzz.cxx
    day1/rule_of_0_3_5.cxx
    day1/shared_ptr_workings.cxx
    day1/surprise_remove_does_not_remove.cxx
    day1/composition_via_private_inheritance.cxx
    day1/solid.cxx
    day1/unsorted.cxx)
target_link_libraries(examples PRIVATE gmock_main gtest gmock)
add_test(example_tests COMMAND examples)
