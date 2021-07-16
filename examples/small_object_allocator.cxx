#include <bitset>
#include <vector>

// don't use with structs/classes with ctor/dtor
template <typename T, std::size_t Size>
class SmallObjectAllocator {
public:
	SmallObjectAllocator() : memory(Size) {
	}

	T* allocate() {
		for (std::size_t n = 0; n < Size; ++n) {
			if (!usage[n]) {
				usage[n] = true;
				return &(memory[n]);
			}
		}
		return nullptr;
	}

	void release(T* ptr) {
		std::size_t const index = ptr - memory.data();
		usage[index] = false;
	}

private:
	std::vector<T> memory;
	std::bitset<Size> usage{};
};

template <typename T>
class List {
public:
	struct Item {
		T value;
		Item * next;
	};

	List(SmallObjectAllocator<Item, 10000> * allocator)
		: allocator{ allocator }
	{}

	void push_front(T const& value) {
		auto const oldHead = head;
		head = allocator->allocate();
		head->value = value;
		head->next = oldHead;
	}

private:

	Item* head = nullptr;
	SmallObjectAllocator<Item, 10000> * allocator;
};
