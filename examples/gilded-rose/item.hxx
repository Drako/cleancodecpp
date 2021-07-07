#pragma once

#ifndef ITEM_HXX
#define ITEM_HXX

#include <ostream>
#include <string>

struct Item final {
    std::string name;
    int sellIn;
    int quality;
};

inline std::ostream& operator << (std::ostream& os, Item const& it) {
    return os
        << "Item[name=\""
        << it.name
        << "\", sellIn="
        << it.sellIn
        << ", quality="
        << it.quality
        << "]";
}

inline bool operator == (Item const& lhs, Item const& rhs) {
    return lhs.name == rhs.name
        && lhs.sellIn == rhs.sellIn
        && lhs.quality == rhs.quality;
}

inline bool operator != (Item const& lhs, Item const& rhs) {
    return lhs.name != rhs.name
        || lhs.sellIn != rhs.sellIn
        || lhs.quality != rhs.quality;
}

#endif // ITEM_HXX
