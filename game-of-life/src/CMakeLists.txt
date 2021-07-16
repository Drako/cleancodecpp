add_executable(GameOfLife main.cxx)
target_link_libraries(GameOfLife PRIVATE
	CONAN_PKG::boost
	Boost::DI
)
