add_executable(BowlingGameTests
	bowling_game.cxx bowling_game.hxx
	bowling_game_tests.cxx
)
target_link_libraries(BowlingGameTests PRIVATE CONAN_PKG::gtest)

add_test(NAME BowlingGameTests COMMAND BowlingGameTests)
