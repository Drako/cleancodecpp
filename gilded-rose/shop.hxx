#pragma once

#ifndef SHOP_HXX
#define SHOP_HXX

#include "item.hxx"

#include <vector>

class Shop final {
	std::vector<Item> items;

public:
	explicit Shop(std::vector<Item> items);

	std::vector<Item> const& getItems() const;

	void updateQuality();
};

#endif // SHOP_HXX
