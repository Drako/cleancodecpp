#include <gtest/gtest.h>

#include <algorithm>
#include <iterator>
#include <vector>

TEST(SurpriseTest, remove_does_not_remove)
{
    using namespace std;

    vector numbers { 1, 2, 3, 4, 5, 6 };

    // remove only moves the values to be kept to the front, leaving excessive values at the end
    auto const marked_for_removal = remove_if(
        begin(numbers),
        end(numbers),
        [](int n) { return n % 2 != 0; });

    // notice how the last three numbers are unchanged
    EXPECT_EQ((std::vector { 2, 4, 6, 4, 5, 6 }), numbers);

    // so afterwards erase needs to be used
    numbers.erase(marked_for_removal, end(numbers));

    EXPECT_EQ((std::vector { 2, 4, 6 }), numbers);
}
