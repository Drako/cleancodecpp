#include <memory>


int a = 0;

struct Foo {
	std::unique_ptr<int> a;
	std::unique_ptr<int> b;
};

// could leak memory if after new int an exception is thrown
std::unique_ptr<Foo> ptr{ new Foo {
	std::unique_ptr<int>{new int{23}},
	std::unique_ptr<int>{new int{42}}
} };

struct Holder {
	int* data;
	int refCount;
	int weakCount;
};

struct WeakPtr {
	Holder * holder;

	bool isValid() const {
		return holder->refCount > 0;
	}

	WeakPtr(Holder * holder) : holder{ holder } {
		++holder->weakCount;
	}

	~WeakPtr() {
		--holder->weakCount;
		if (holder->weakCount == 0) {
			delete holder;
		}
	}
};

// 0 3 5 rule

// 0 = no dtor
// 3 = dtor + copy ctor + copy assign
// 5 = dtor + copy ctor + copy assign + move ctor + move assign
struct UniquePtr {
	~UniquePtr() {
		// delete
	}

	UniquePtr(UniquePtr const&) = delete;
	UniquePtr & operator = (UniquePtr const&) = delete;

	UniquePtr(UniquePtr&&) = delete;
	UniquePtr & operator = (UniquePtr&&) = delete;
};

struct SharedPtr {

	Holder* holder;

	//SharedPtr(int* ptr) : holder{ new Holder{ptr, 1, 0} };

	// dtor
	// copy ctor/copy assignment
	// seit C++11
	// move ctor/move assignment

	SharedPtr(SharedPtr const& src) : holder{ src.holder } {
		++holder->refCount;
	}

	~SharedPtr() {
		--holder->refCount;
		if (holder->refCount == 0) {
			delete holder->data;
		}
		if (holder->weakCount == 0) {
			delete holder;
		}
	}

	WeakPtr getWeak() const {
		return { holder };
	}
};

struct List {
	struct Item {
		int value;
		std::shared_ptr<Item> next;
		std::weak_ptr<Item> prev;
	};
};

// circular dependencies
std::shared_ptr<T>
std::weak_ptr<T>

std::unique_ptr<T>
T*

// safe against exceptions
std::make_unique<Foo>(std::make_unique<int>(23), std::make_unique<int>(42));

std::unique_ptr<int> ptr = std::make_unique<int>(23);
std::shared_ptr<int>;

class Point final {
	int x, y;

public:
	int& getX();
	int getX() const;
};

#include <mutex>

template <typename T>
class Vector {
	T*data;
	int size;
	int capacity;
	mutable std::mutex mutex;

public:
	Vector() {

	}

	~Vector() {
		delete[] data;
	}

	T& operator[](int index);
	T const& operator[](int index) const {
		std::lock_guard<std::mutex> lock{ mutex };
	}
};

void foo() {
	Point const p;
	p.getX();

	Vector<int> v{ 23, 42, 1337 };
	v[10] = 23;
}


// konstanter Wert vom Typ T
// T const
// const T

/*
variabler Zeiger auf variablen Speicher
T*

variable Zeiger auf konstanten Speicher
const T*
T const*

konstanten Zeiger auf variablen Speicher
T* const

konstanten Zeiger auf konstanten Speicher
const T* const
T const * const

east-const/west-const

T const ** const
konstanten Zeiger auf einen variablen Zeiger auf konstanten Speicher
*/

// singleton bad

/* bad example:
// don't forget to reset
bool useFile = false;
void copy();
*/

/*
immutable local  | mutable local
-----------------+---------------
immutable shared | mutable shared
*/
