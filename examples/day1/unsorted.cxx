#include <gtest/gtest.h>

// TODO: make more accessible

#include <algorithm>
#include <atomic>
#include <cctype>
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <memory>
#include <mutex>
#include <set>
#include <string_view>
#include <vector>

std::weak_ptr<int> a()
{
    std::unique_ptr<int> { (int*)0xFFFFFFFFF };

    std::shared_ptr<int> one = std::make_shared<int>(42);
    std::shared_ptr<int> two { one };

    std::weak_ptr<int> sub_two { two };
    auto ptr = sub_two.lock();

    return sub_two;
}

std::mutex mtx;

void locking()
{
    std::lock_guard<std::mutex> lock { mtx };
}

TEST(FiddleTest, filtering)
{
    std::vector<int> numbers { 1, 2, 3, 4, 5, 6 };

    std::vector<int> even {};
    //even.reserve(3u);
    std::copy_if(
        numbers.begin(),
        numbers.end(),
        std::back_inserter(even),
        [](int n) { return n % 2 == 0; });
    EXPECT_EQ((std::vector { 2, 4, 6 }), even);
}

#include <vector>

/*void foo()
{
    int bar[23];

    std::vector<int> container {};
    // .begin()
    // .end()
    // .cbegin()
    // .cend()
    // std::cbegin()

    int index = 0;
    for (auto const element : bar) {
        ++index;
    }
}*/
