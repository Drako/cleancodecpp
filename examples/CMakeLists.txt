add_executable(examples fiddle.cxx)
target_link_libraries(examples PRIVATE gmock_main gtest gmock)
add_test(example_tests COMMAND examples)
