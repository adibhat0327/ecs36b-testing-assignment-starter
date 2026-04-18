#include <cstdlib>
#include <vector>
#include <algorithm>
#include "gtest/gtest.h"
#include "sorting.h"
#include "rapidcheck/gtest.h"
#include "test_helpers.h"

TEST(MakeSortedTests, SimpleSortSortedArray) {
    /*
     * Check that we can sort an array that is already sorted.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int ar[] = {1, 2, 3, 4, 5};
    int expected[] = {1, 2, 3, 4, 5};
    make_sorted(ar, 5);
    for (int i = 0; i < 5; ++i) {
        EXPECT_EQ(ar[i], expected[i]);
    }
}

TEST(MakeSortedTests, SimpleSortReverseSortedArray) {
    /*
     * Check that we can sort an array that is reverse sorted order.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int ar[] = {5, 4, 3, 2, 1};
    int expected[] = {1, 2, 3, 4, 5};
    make_sorted(ar, 5);
    for (int i = 0; i < 5; ++i) {
        EXPECT_EQ(ar[i], expected[i]);
    }
}


TEST(MakeSortedTests, SimpleSortAverageArray) {
    /*
     * Check that we can sort an array where the elements in it are in random order.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int ar[] = {12, 45, 10, 8, 13};
    int expected[] = {8, 10, 12, 13, 45};
    make_sorted(ar, 5);
    for (int i = 0; i < 5; ++i) {
        EXPECT_EQ(ar[i], expected[i]);
    }
}

TEST(MakeSortedTests, SimpleSortArrayWithDuplicates) {
    /*
     * Check that we can sort an array where there are duplicate elements in it.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int ar[] = {5, 5, 6, 3};
    int expected[] = {3, 5, 5, 6};
    make_sorted(ar, 4);
    for (int i = 0; i < 4; ++i) {
        EXPECT_EQ(ar[i], expected[i]);
    }
}

RC_GTEST_PROP(MakeSortedTests,
              PropertyAfterSortingValuesAreInAscendingOrder,
              (std::vector<int> values)
) {
    /* Test that after sorting an array, the values are in ascending order
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    RC_PRE(!values.empty());
    int* ar = new int[values.size()];
    copy_vector_to_array(values, ar);
    make_sorted(ar, (int)values.size());
    for (size_t i = 1; i < values.size(); ++i) {
        RC_ASSERT(ar[i - 1] <= ar[i]);
    }
    delete[] ar;
}
