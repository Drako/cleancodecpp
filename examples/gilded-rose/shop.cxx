#include "shop.hxx"

#include <algorithm>

namespace {
int calculateQuality(ItemType type, int quality, int sellIn)
{
    if (quality < Item::MIN_QUALITY || quality > Item::MAX_QUALITY) {
        return quality;
    }

    switch (type) {
    default:
        quality -= sellIn < 0 ? 2 : 1;
        break;
    case ItemType::Aged:
        quality += sellIn < 0 ? 2 : 1;
        break;
    case ItemType::Ticket:
        if (sellIn < 0) {
            quality = 0;
        } else if (sellIn < 5) {
            quality += 3;
        } else if (sellIn < 10) {
            quality += 2;
        } else if (sellIn < 15) {
            ++quality;
        }
        break;
    }

    return std::clamp(quality, Item::MIN_QUALITY, Item::MAX_QUALITY);
}
}

Shop::Shop(std::vector<Item> items)
    : items { std::move(items) }
{
}

std::vector<Item> const& Shop::getItems() const
{
    return items;
}

void Shop::updateQuality()
{
    for (auto& item : items) {
        ItemType const type = typeOf(item);

        if (type == ItemType::Legendary) {
            continue;
        }

        --item.sellIn;
        item.quality = ::calculateQuality(type, item.quality, item.sellIn);
    }
}
