/*
class Rectangle {
public:
	Rectangle(int width, int height)
		: width{width}, height{height}
	{}

	int getWidth() { return width; }
	int getHeight() { return height; }

protected:
	int width, height;
};

struct Square : public Rectangle {
public:
	Square(int sideLength)
		: Rectangle{sideLength, sideLength}
	{}
};
*/

struct Shape {
	virtual ~Shape() noexcept = default;

	virtual int area() const = 0;
};

struct Square : Shape {
	int sideLength;

	int area() const override {
		return sideLength * sideLength;
	}
};

int calculate_area(Shape const& s) {
	return s.area();
}

struct Rectangle : Shape {
	int width, height;

	int area() const override {
		return width * height;
	}
};

int calculate_area(Square const& s) {
	if (auto r = dynamic_cast<Rectangle const*>(&s); r != nullptr) {
		return r->sideLength * r->otherSideLength;
	}

	return s.sideLength * s.sideLength;
}

/*
int a{ 23 };
int arr[2]{ 0, 23 };
std::string s{ "foo" };

struct Point {
	int x, y;
};

#include <initializer_list>

template <typename T>
struct DynArray {
	DynArray(int size) {}

	DynArray(std::initializer_list<T> const& init) {
		data = new T[init.size()];
		for (auto idx = init.size(); idx--;) {
			data[idx] = init[idx];
		}
	}

private:
	T*data;
};

DynArray<int> arr2{ 23 };
DynArray<int> arr3( 23 );

Point p{ 23, 42 };
*/
