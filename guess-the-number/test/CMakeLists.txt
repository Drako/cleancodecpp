add_executable(GuessTheNumberTests
	GuessTheNumberTest.cxx
	MockRandomNumberGenerator.hxx
	)
target_link_libraries(GuessTheNumberTests PRIVATE
	GuessTheNumberImpl
	CONAN_PKG::gtest
)

add_test(NAME tests COMMAND GuessTheNumberTests)
