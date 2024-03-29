#include "shop.hxx"

Shop::Shop(std::vector<Item> items)
	: items{ std::move(items) }
{}

std::vector<Item> const& Shop::getItems() const {
	return items;
}

void Shop::updateQuality() {
	for (auto& item : items) {
		if (item.name != "Aged Brie" && item.name != "Backstage passes to a TAFKAL80ETC concert") {
			if (item.quality > 0) {
				if (item.name != "Sulfuras, Hand of Ragnaros") {
					--item.quality;
				}
			}
		}
		else {
			if (item.quality < 50) {
				++item.quality;

				if (item.name == "Backstage passes to a TAFKAL80ETC concert") {
					if (item.sellIn < 11) {
						if (item.quality < 50) {
							++item.quality;
						}
					}

					if (item.sellIn < 6) {
						if (item.quality < 50) {
							++item.quality;
						}
					}
				}
			}
		}

		if (item.name != "Sulfuras, Hand of Ragnaros") {
			--item.sellIn;
		}

		if (item.sellIn < 0) {
			if (item.name != "Aged Brie") {
				if (item.name != "Backstage passes to a TAFKAL80ETC concert") {
					if (item.quality > 0) {
						if (item.name != "Sulfuras, Hand of Ragnaros") {
							--item.quality;
						}
					}
				}
				else {
					item.quality -= item.quality;
				}
			}
			else {
				if (item.quality < 50) {
					++item.quality;
				}
			}
		}
	}
}
