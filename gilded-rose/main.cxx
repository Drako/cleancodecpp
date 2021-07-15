#include <iostream>

#include "shop.hxx"

int main()
{
	auto const create_items = []() {
		std::vector<Item> items;

		items.push_back({ "+5 Dexterity Vest", 10, 20 });
		items.push_back({ "Aged Brie", 2, 0 });
		items.push_back({ "Elixir of the Mongoose", 5, 7 });
		items.push_back({ "Sulfuras, Hand of Ragnaros", 0, 80 });
		items.push_back({ "Backstage passes to a TAFKAL80ETC concert", 15, 20 });

		// this Conjured item doesn't yet work properly
		items.push_back({ "Conjured Mana Cake", 3, 6 });

		return items;
	};

	std::cout << "OMGHAI!\n";

	Shop shop{ create_items() };

	for (int day = 0; day <= 30; ++day)
	{
		std::cout << "-------- day " << day << " --------\n";
		for (auto& item : shop.getItems())
		{
			std::cout << item << "\n";
		}
		std::cout << "\n";
		shop.updateQuality();
	}

	std::cout << std::endl;
	return 0;
}
