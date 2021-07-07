#include "shop.hxx"

#include <algorithm>
#include <functional>
#include <map>

namespace {
int regularQuality(int quality, int sellIn)
{
    return quality - (sellIn < 0 ? 2 : 1);
}

int agedQuality(int quality, int sellIn)
{
    return quality + (sellIn < 0 ? 2 : 1);
}

int ticketQuality(int quality, int sellIn)
{
    if (sellIn < 0) {
        return 0;
    } else if (sellIn < 5) {
        return quality + 3;
    } else if (sellIn < 10) {
        return quality + 2;
    } else {
        return quality + 1;
    }
}

int calculateQuality(ItemType type, int quality, int sellIn)
{
    if (quality < Item::MIN_QUALITY || quality > Item::MAX_QUALITY) {
        return quality;
    }

    static std::map<ItemType, std::function<int(int, int)>> const updaters {
        { ItemType::Regular, &regularQuality },
        { ItemType::Aged, &agedQuality },
        { ItemType::Ticket, &ticketQuality },
    };

    auto const updater = updaters.find(type);
    if (updater == updaters.end()) {
        throw std::invalid_argument { "Unsupported type!" };
    }

    return std::clamp(
        updater->second(quality, sellIn),
        Item::MIN_QUALITY,
        Item::MAX_QUALITY);
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
