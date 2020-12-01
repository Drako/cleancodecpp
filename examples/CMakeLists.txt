add_executable(examples fiddle.cxx)
target_link_libraries(examples PRIVATE gtest_main gtest gmock)
add_test(example_tests COMMAND examples)
