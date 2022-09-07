#include <gtest/gtest.h>

#include "shop.hxx"

TEST(GildedRoseTest, shopCanBeConstructed) {
	std::vector<Item> items;
	Shop shop{ std::move(items) };

	EXPECT_TRUE(shop.getItems().empty());
}
