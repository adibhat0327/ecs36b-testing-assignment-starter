#include <cstdlib>
#include <vector>
#include <algorithm>
#include "gtest/gtest.h"
#include "sorting.h"
#include "test_helpers.h"
#include "rapidcheck/gtest.h"

TEST(GetSortedTests, SimpleSortSortedArray) {
    /*
     * Check that we can sort an array that is already sorted.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int ar[] = {1, 2, 3, 4, 5};
    int expected[] = {1, 2, 3, 4, 5};
    int* sorted = get_sorted(ar, 5);
    for (int i = 0; i < 5; ++i) {
        EXPECT_EQ(sorted[i], expected[i]);
    }
    free(sorted);
}

TEST(GetSortedTests, SimpleSortReverseSortedArray) {
    /*
     * Check that we can sort an array that is reverse sorted order.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int ar[] = {5, 4, 3, 2, 1};
    int expected[] = {1, 2, 3, 4, 5};
    int* sorted = get_sorted(ar, 5);
    for (int i = 0; i < 5; ++i) {
        EXPECT_EQ(sorted[i], expected[i]);
    }
    free(sorted);
}

TEST(GetSortedTests, SimpleSortAverageArray) {
    /*
     * Check that we can sort an array where the elements in it are in random order.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int ar[] = {12, 45, 10, 8, 13};
    int expected[] = {8, 10, 12, 13, 45};
    int* sorted = get_sorted(ar, 5);
    for (int i = 0; i < 5; ++i) {
        EXPECT_EQ(sorted[i], expected[i]);
    }
    free(sorted);
}

TEST(GetSortedTests, SimpleSortArrayWithDuplicates) {
    /*
     * Check that we can sort an array where there are duplicate elements in it.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int ar[] = {5, 5, 6, 3};
    int expected[] = {3, 5, 5, 6};
    int* sorted = get_sorted(ar, 4);
    for (int i = 0; i < 4; ++i) {
        EXPECT_EQ(sorted[i], expected[i]);
    }
    free(sorted);
}

TEST(GetSortedTests, SimpleOriginalDoesNotChange) {
    /*
     * Check that the original array was not modified.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int ar[] = {12, 45, 10, 8, 13};
    int original[] = {12, 45, 10, 8, 13};
    int* sorted = get_sorted(ar, 5);
    for (int i = 0; i < 5; ++i) {
        EXPECT_EQ(ar[i], original[i]);
    }
    free(sorted);
}

TEST(GetSortedTests, SimpleCopyWasMade) {
    /*
     * Check that the sorted array is copy of the original array in sorted order.
     * (ar and copy point to different locations in memory and no parts of the two arrays overlap)
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int ar[] = {3, 1, 2};
    int* sorted = get_sorted(ar, 3);
    EXPECT_NE(sorted, ar);
    free(sorted);
}


RC_GTEST_PROP(GetSortedTests,
              PropertyAfterSortingValuesAreInAscendingOrder,
              (std::vector<int> values)
) {
    /* Check that after sorting an array, the values are in ascending order
     * Don't forget to free any memory that was dynamically allocated as part of this test
     */
    RC_PRE(!values.empty());
    int* ar = new int[values.size()];
    copy_vector_to_array(values, ar);
    int* sorted = get_sorted(ar, (int)values.size());
    for (size_t i = 1; i < values.size(); ++i) {
        RC_ASSERT(sorted[i - 1] <= sorted[i]);
    }
    free(sorted);
    delete[] ar;
}

RC_GTEST_PROP(GetSortedTests,
              PropertyOriginalDoesNotChange,
              (const std::vector<int>& values)
) {
    /*
     * Check that the original array was not modified.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    RC_PRE(!values.empty());
    int* ar = new int[values.size()];
    copy_vector_to_array(values, ar);
    int* sorted = get_sorted(ar, (int)values.size());
    RC_ASSERT(elements_in_vector_and_array_are_same(values, ar));
    free(sorted);
    delete[] ar;
}

RC_GTEST_PROP(GetSortedTests,
              PropertyCopyWasMade,
              (const std::vector<int>& values)
) {
    /*
     * Check that the sorted array is copy of the original array in sorted order.
     * (ar and copy point to different locations in memory and no parts of the two arrays overlap)
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    RC_PRE(!values.empty());
    int* ar = new int[values.size()];
    copy_vector_to_array(values, ar);
    int* sorted = get_sorted(ar, (int)values.size());
    RC_ASSERT(sorted != ar);
    free(sorted);
    delete[] ar;
}
