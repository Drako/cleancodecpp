add_library(gildedrose_impl STATIC
	item.hxx
	shop.hxx shop.cxx
	)

add_executable(gilded-rose main.cxx)
target_link_libraries(gilded-rose PRIVATE gildedrose_impl)

add_executable(gilded-rose-test test.cxx)
target_link_libraries(gilded-rose-test PRIVATE gildedrose_impl CONAN_PKG::gtest)
add_test(NAME gilded-rose-test COMMAND gilded-rose-test)
