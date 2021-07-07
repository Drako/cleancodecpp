#include <gtest/gtest.h>

#include "shop.hxx"

enum {
    LEGENDARY_QUALITY = 80
};

struct Parameters {
    Item input;
    Item expected;
};

struct GildedRoseTest : ::testing::TestWithParam<Parameters> {
    static Item updateItem(Item const& original, int days = 1)
    {
        Shop shop { { original } };
        for (int n = 0; n < days; ++n) {
            shop.updateQuality();
        }
        return shop.getItems().front();
    }
};

TEST_P(GildedRoseTest, item_get_updated_correctly)
{
    auto const [input, expected] = GetParam();
    EXPECT_EQ(expected, updateItem(input));
}

INSTANTIATE_TEST_SUITE_P(
    GildedRoseTest,
    GildedRoseTest,
    ::testing::Values(
        Parameters {
            Item { "Sulfuras, Hand of Ragnaros", 0, LEGENDARY_QUALITY },
            Item { "Sulfuras, Hand of Ragnaros", 0, LEGENDARY_QUALITY } },
        Parameters {
            Item { "Aged Brie", 2, 0 },
            Item { "Aged Brie", 1, 1 } },
        Parameters {
            Item { "Aged Brie", -1, 5 },
            Item { "Aged Brie", -2, 7 } },
        Parameters {
            Item { "Backstage passes to a TAFKAL80ETC concert", 15, 20 },
            Item { "Backstage passes to a TAFKAL80ETC concert", 14, 21 } },
        Parameters {
            Item { "Backstage passes to a TAFKAL80ETC concert", 10, 25 },
            Item { "Backstage passes to a TAFKAL80ETC concert", 9, 27 } },
        Parameters {
            Item { "Backstage passes to a TAFKAL80ETC concert", 5, 35 },
            Item { "Backstage passes to a TAFKAL80ETC concert", 4, 38 } },
        Parameters {
            Item { "Backstage passes to a TAFKAL80ETC concert", 0, 50 },
            Item { "Backstage passes to a TAFKAL80ETC concert", -1, 0 } },
        Parameters {
            Item { "dummy", 10, 10 },
            Item { "dummy", 9, 9 } },
        Parameters {
            Item { "dummy", -1, 10 },
            Item { "dummy", -2, 8 } }));
