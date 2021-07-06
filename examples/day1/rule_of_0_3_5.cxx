// Rule of 0 -> POD (Plain Old Data)
struct Point {
    int x;
    int y;
};

// Rule of 3 -> As soon as there is a destructor,
// also copy constructor and copy assignment must be defined or deleted
// See https://en.cppreference.com/w/cpp/language/rule_of_three
template <typename T>
class ScopedPtr final {
public:
    explicit ScopedPtr(T* ptr = nullptr)
        : ptr { ptr }
    {
    }

    ~ScopedPtr()
    {
        delete ptr;
    }

    ScopedPtr(ScopedPtr const& src) = delete;
    ScopedPtr& operator=(ScopedPtr const& src) = delete;

private:
    T* ptr;
};

// Rule of 5
// like Rule of 3, but with move
template <typename T>
class UniquePtr final {
public:
    constexpr explicit UniquePtr(T* ptr = nullptr) noexcept
        : ptr { ptr }
    {
    }

    ~UniquePtr()
    {
        delete ptr;
    }

    UniquePtr(UniquePtr const& src) = delete;
    UniquePtr& operator=(UniquePtr const& src) = delete;

    constexpr UniquePtr(UniquePtr&& src) noexcept
        : ptr { src.ptr }
    {
        src.ptr = nullptr;
    }

    UniquePtr& operator=(UniquePtr&& src) noexcept
    {
        delete ptr;
        ptr = src.ptr;
        return *this;
    }

private:
    T* ptr;
};
