#include <atomic>

template <typename T>
struct Holder {
    std::atomic<int> ref_count;
    std::atomic<int> weak_count;
    T* data;
};

template <typename T>
class Ptr {
    Holder<T>* holder;

    // TODO: add example implementation with comments
};
