add_executable(GameOfLifeTests
	ConsoleUserInterfaceTest.cxx
	GameTest.cxx
	MockUserInterface.hxx
	WorldTest.cxx
)
target_link_libraries(GameOfLifeTests PRIVATE GameOfLifeImpl CONAN_PKG::gtest)

add_test(NAME GameOfLifeTests COMMAND GameOfLifeTests)
