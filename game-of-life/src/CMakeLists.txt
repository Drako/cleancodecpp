add_library(GameOfLifeImpl SHARED
	CellState.hxx
	ConsoleUserInterface.cxx ConsoleUserInterface.hxx
	Game.hxx Game.cxx
	UserInterface.hxx
	World.cxx World.hxx
	DllInterface.hxx
)
target_compile_definitions(GameOfLifeImpl PRIVATE BUILD_DLL=1)
target_include_directories(GameOfLifeImpl PUBLIC "${CMAKE_CURRENT_INCLUDE_DIR}")

add_executable(GameOfLife main.cxx)
target_link_libraries(GameOfLife PRIVATE
	GameOfLifeImpl
	Boost::DI
)
