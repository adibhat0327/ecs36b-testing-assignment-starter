#include <cstdlib>
#include <vector>
#include <algorithm>
#include "test_helpers.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "sorting.h"
#include "rapidcheck/gtest.h"


TEST(SwapTests, SimpleSwapTwoValues) {
    /*
     * Swap two values and see if the swap was successful.
     */
    int a = 5, b = 10;
    swap(&a, &b);
    EXPECT_EQ(a, 10);
    EXPECT_EQ(b, 5);
}

TEST(SwapTests, SimpleSwapValuesInArray) {
    /*
     * Swap a few values in an array.
     * Check that the ones that swapped did swap and the ones that didn't swap
     * are still at the same locations
     */
    int ar[] = {1, 2, 3, 4, 5};
    swap(&ar[1], &ar[3]);
    EXPECT_EQ(ar[0], 1);
    EXPECT_EQ(ar[1], 4);
    EXPECT_EQ(ar[2], 3);
    EXPECT_EQ(ar[3], 2);
    EXPECT_EQ(ar[4], 5);
}

RC_GTEST_PROP(SwapTests,
              PropertySwapTwoValues,
              (int a_start, int b_start)
) {
    /*
     * Swap two values and see if the swap was successful.
     */
    int a = a_start, b = b_start;
    swap(&a, &b);
    RC_ASSERT(a == b_start);
    RC_ASSERT(b == a_start);
}


RC_GTEST_PROP(SwapTests,
              PropertySwapValuesInArray,
              (const std::vector<int>& values)
) {
    /*
     * Swap two values in an array. See that they swapped and the others did not
     */
    RC_PRE(values.size() >= 2);
    int* ar = new int[values.size()];
    copy_vector_to_array(values, ar);
    swap(&ar[0], &ar[1]);
    RC_ASSERT(ar[0] == values[1]);
    RC_ASSERT(ar[1] == values[0]);
    for (size_t i = 2; i < values.size(); ++i) {
        RC_ASSERT(ar[i] == values[i]);
    }
    delete[] ar;
}
