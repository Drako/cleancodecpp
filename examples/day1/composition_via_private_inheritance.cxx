struct QuickSort {
    template <typename Container>
    static void sort(Container& c);
};
struct MergeSort {
    template <typename Container>
    static void sort(Container& c);
};

// Sorter HAS a Strategy, it ISn't one
template <typename Strategy = QuickSort>
struct Sorter : private Strategy {
    template <typename Container>
    static void sort(Container& c)
    {
        // despite looking like a static function call, this isn't one
        // it is a regular member function call, just that we state explicitly
        // from which relative we want to have it
        Strategy::sort(c);
    }
};
