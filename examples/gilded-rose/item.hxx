#pragma once

#ifndef ITEM_HXX
#define ITEM_HXX

#include <ostream>
#include <string>
#include <unordered_map>

struct Item final {
    std::string name;
    int sellIn;
    int quality;

    constexpr static int const MIN_QUALITY = 0;
    constexpr static int const MAX_QUALITY = 50;
};

enum class ItemType {
    Legendary,
    Aged,
    Ticket,
    Regular,
};

inline ItemType typeOf(Item const& item)
{
    static std::unordered_map<std::string, ItemType> const typeMap {
        { "Sulfuras, Hand of Ragnaros", ItemType::Legendary },
        { "Aged Brie", ItemType::Aged },
        { "Backstage passes to a TAFKAL80ETC concert", ItemType::Ticket },
    };

    auto const it = typeMap.find(item.name);
    return it == typeMap.end() ? ItemType::Regular : it->second;
}

inline std::ostream& operator<<(std::ostream& os, Item const& it)
{
    return os
        << "Item[name=\""
        << it.name
        << "\", sellIn="
        << it.sellIn
        << ", quality="
        << it.quality
        << "]";
}

inline bool operator==(Item const& lhs, Item const& rhs)
{
    return lhs.name == rhs.name
        && lhs.sellIn == rhs.sellIn
        && lhs.quality == rhs.quality;
}

inline bool operator!=(Item const& lhs, Item const& rhs)
{
    return lhs.name != rhs.name
        || lhs.sellIn != rhs.sellIn
        || lhs.quality != rhs.quality;
}

#endif // ITEM_HXX
