#include "shop.hxx"

#include <algorithm>
#include <map>

namespace {
	using QualityCalculator = int(*)(int, int);

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
		}
		else if (sellIn < 5) {
			return quality + 3;
		}
		else if (sellIn < 10) {
			return quality + 2;
		}
		else {
			return quality + 1;
		}
	}

	QualityCalculator getCalculatorFor(ItemType const type) {
		static std::map<ItemType, QualityCalculator> const calculators{
			{ ItemType::Regular, &regularQuality },
			{ ItemType::Aged, &agedQuality },
			{ ItemType::Ticket, &ticketQuality },
		};

		auto const it = calculators.find(type);
		if (it == calculators.end()) {
			throw std::invalid_argument{ "Unsupported type!" };
		}

		return it->second;
	}

	int calculateQuality(ItemType type, int quality, int sellIn)
	{
		if (quality < Item::MIN_QUALITY || quality > Item::MAX_QUALITY) {
			return quality;
		}

		auto const calculator = getCalculatorFor(type);

		return std::clamp(
			calculator(quality, sellIn),
			Item::MIN_QUALITY,
			Item::MAX_QUALITY);
	}
}

Shop::Shop(std::vector<Item> items)
	: items{ std::move(items) }
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
