#include <gtest/gtest.h>

#include "shop.hxx"

struct GildedRoseTest : ::testing::Test {
    static Item updateItem(Item const& original, int days = 1)
    {
        Shop shop{ {original} };
        for (int n = 0; n < days; ++n) {
            shop.updateQuality();
        }
        return shop.getItems().front();
    }
};

TEST_F(GildedRoseTest, legendaryItemsNeverChange) {
    Item const sulfuras{ "Sulfuras, Hand of Ragnaros", 0, 80 };
    Item const updated = updateItem(sulfuras);
    EXPECT_EQ(sulfuras, updated);
}
