#pragma once

#include <cstddef>

#include <stdexcept>

namespace workshop {

template <typename T>
class List {
public:
    inline List(...)
    {
        // TODO: replace with actual constructor... this one is only to make the tests compile
    }

    inline bool empty() const
    {
        // TODO: implement
        return true;
    }

    inline std::size_t size() const
    {
        // TODO: implement
        return 0u;
    }

    inline void push_front(T const& item)
    {
        // TODO: implement
    }

    inline T& front()
    {
        // TODO: implement
        static T dummy {};
        return dummy;
    }

    inline T front() const
    {
        // TODO: implement
        return {};
    }

    inline void pop_front()
    {
        // TODO: implement
    }
};

}
