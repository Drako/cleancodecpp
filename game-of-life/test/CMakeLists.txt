add_executable(GameOfLifeTests
	ConsoleUserInterfaceTest.cxx
	GameTest.cxx
	MockRandomizer.hxx
	MockUserInterface.hxx
	StdRandomizerTest.cxx
	WorldTest.cxx
)
target_link_libraries(GameOfLifeTests PRIVATE GameOfLifeImpl CONAN_PKG::gtest)

add_test(NAME GameOfLifeTests COMMAND GameOfLifeTests)
