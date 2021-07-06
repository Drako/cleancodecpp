#pragma once

#include <cstddef>

#include <initializer_list>
#include <memory>
#include <stdexcept>
#include <type_traits>

namespace workshop {

template <typename T>
class List {
    struct Item {
        T value;
        Item* next;
    };

public:
    List() = default;

    inline List(std::initializer_list<T> const& values)
    {
        if (values.size() == 0) {
            return;
        }

        for (auto it = values.end() - 1; it >= values.begin(); --it) {
            push_front(*it);
        }
    }

    inline ~List()
    {
        while (!empty()) {
            pop_front();
        }
    }

    List(List const&) = delete;
    List& operator=(List const&) = delete;

    inline bool empty() const
    {
        return items == 0;
    }

    inline std::size_t size() const
    {
        return items;
    }

    inline void push_front(T const& item)
    {
        root = new Item { item, root };
        ++items;
    }

    inline T& front()
    {
        return root->value;
    }

    inline T const& front() const
    {
        return root->value;
    }

    inline void pop_front()
    {
        auto const old_root = root;
        root = root->next;
        --items;
        delete old_root;
    }

private:
    Item* root { nullptr };
    std::size_t items { 0u };
};

}
