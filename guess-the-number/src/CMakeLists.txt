add_library(GuessTheNumberImpl STATIC
	GuessTheNumber.hxx GuessTheNumber.cxx
	CheckResult.hxx
	RandomNumberGenerator.hxx
	StdRandomNumberGenerator.hxx
	UserInterface.hxx
	ConsoleUserInterface.hxx ConsoleUserInterface.cxx
)
target_include_directories(GuessTheNumberImpl INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(GuessTheNumber main.cxx)
target_link_libraries(GuessTheNumber PRIVATE
	GuessTheNumberImpl
	CONAN_PKG::boost
	Boost::DI
)
